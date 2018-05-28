#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 销量预测(DMS)
#
# 1. 状态位1、2、3、4、4G、5、7的商品参与DMS计算(物美举例).
# 2. 商品状态发生变化时,取最近的DMS作为公式中的历史DMS.
# 3. 系统已有商品,大数据计算DMS时,初始DMS取SAP计算的DMS,不要置0(第一次全量读取SAP DMS).
# 4. 商品无历史销售记录时,DMS初始值为0;过去一年都没有销售的,不管是正常还是促销都是0.
# 5. 如果昨日库存<=0.25倍前一日的DMS,则昨日不更新DMS(表示需要取两日DMS).

# DMS表说明(venderdb.dms_data)
#
#                   werks | 门店
#                     sku | 商品
#                     dms | DMS
#                   dms_n | 正常 DMS
#                   dms_p | 促销 DMS
#                  status | 商品状态
#               sale_flag | 过去一年是否有销售(0:无 1:有)
#                 dms_old | 昨日 DMS
#               dms_n_old | 昨日正常 DMS
#               dms_p_old | 昨日促销 DMS
#       yesterday_is_prom | 昨日是否促销
# yesterday_is_prom_start | 昨日是否开裆日
#     today_is_prom_start | 今天是否开裆日
#                    sale | 昨日销量
#                   stock | 昨日库存
#                salerate | 销量比例
#              olddmsrate | 昨日 DMS 比例
#               date_type | 是否工作日(0:工作日 1:节假日)
#               vender_id | 商家ID
#                      dt | 分区日期(RUNDATE)

import json
import logging
import datetime
import pyspark.sql.functions as F
from pyspark.sql import SparkSession
from pyspark.sql.types import IntegerType, FloatType
from pyspark.sql.types import ArrayType, StructType, StructField

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::dms") \
                    .config("spark.sql.tungsten.enabled", "false") \
                    .config("spark.sql.crossJoin.enabled", "true") \
                    .config("spark.serializer", "org.apache.spark.serializer.KryoSerializer") \
                    .config("spark.default.parallelism", 60) \
                    .config("hive.exec.dynamic.partition", "true") \
                    .config("hive.exec.dynamic.partition.mode", "nonstrict") \
                    .config("hive.exec.max.dynamic.partitions", "10000") \
                    .enableHiveSupport() \
                    .getOrCreate()

RUNDATE = '20180501'

# 供商配置数据及生效时间
CONFJSON = None
CONFDATE = None

MANDT = '300'
VENDERID = '1'
VENDERDB = 'wumart2dmall'


def WITHDB(tableName):
    SEP = '.'
    dbtable = VENDERDB + SEP + tableName
    logging.info('WITHDB(): %s', dbtable)
    return dbtable


def savehive(df, partitionCols, partitionKV, dbtable):
    # NOTE: 由于平台权限限制不能用CREATE SQL创建表，这里利用了技巧确保表的自动创建
    df.filter('NULL = NULL') \
      .write \
      .mode('append') \
      .partitionBy(partitionCols) \
      .saveAsTable(dbtable)
    # FIXME: 将df分区字段drop掉，INSERT OVERWRITE已经包含了分区字段KV（无奈的做法!!!）
    for col in partitionCols:
        df = df.drop(col)
    df.registerTempTable("_temptable_")
    insertsql = "INSERT OVERWRITE TABLE {0} PARTITION({1}) SELECT * FROM _temptable_".format(dbtable, partitionKV)
    logging.info('savehive(): %s', insertsql)
    spark.sql(insertsql)
    df.unpersist()


def fastjoin(leftDF, rightDF, on, how='inner'):
    """
    fastjoin() join leftDF with rightDF, the default join type is inner join.
    fastjoin will repartition both dataframe to speed up this task. When in
    debug, fastjoin will check both dataframes have the expected joined
    columns.
    """
    DEBUG_JOIN = False
    if DEBUG_JOIN:
        lcol, rcol = leftDF.columns, rightDF.columns
        logging.info('fastjoin(): left:%s, right:%s, on:%s, how:%s', lcol, rcol, on, how)
        ucol = list(set(lcol) & set(rcol) & set(on))
        assert len(on) == len(ucol), 'on:%s, &cols:%s' % (len(on), len(ucol))

    N_PARTITIONS = 240
    left = leftDF.repartition(N_PARTITIONS, on)
    right = rightDF.repartition(N_PARTITIONS, on)
    return left.join(right, on, how).cache()


def safeunion(leftDF, rightDF):
    """
    safeunion() composes leftDF and rightDF to get a larger dataframe, which
    has all the rows in them. When in debug, safeunion will check both
    dataframe have the same columns before doing union actually.
    """
    lcol, rcol = leftDF.columns, rightDF.columns
    ucol = list(set(lcol) & set(rcol))

    DEBUG_UNION = False
    if DEBUG_UNION:
        logging.info('safeunion(): left:%s, right:%s', lcol, rcol)
        assert len(lcol) == len(rcol) and len(rcol) == len(ucol), 'lcol:%s, rcol:%s, ucol:%s' % (lcol, rcol, ucol)

    return leftDF.select(ucol).union(rightDF.select(ucol)).cache()


def datenow():
    """
    datenow() returns current date string like '20180408'
    """
    now = datetime.datetime.now()
    nowstr = now.strftime('%Y%m%d')
    logging.info('datenow(): %s', nowstr)
    return nowstr


def datediff(datestr, diff):
    """
    datediff() returns date string which before(diff<0)
    or after(diff>0) diff days against datestr.
    """
    d = datetime.datetime.strptime(datestr, '%Y%m%d')
    diff = datetime.timedelta(days=diff)
    return (d + diff).strftime('%Y%m%d')


def jsonpretty(jsonstr):
    """
    jsonpretty() returns prettified json string, if jsonstr is not
    a valid json string, the raw jsonstr will be returned without
    modification.
    """
    try:
        jsonObj = json.loads(jsonstr)
        prettyJson = json.dumps(jsonObj, indent=4, sort_keys=True, ensure_ascii=False)
    except:
        prettyJson = jsonstr
    return prettyJson


def onedayAgoDMS():
    """昨日DMS"""

    onedayAgo = datediff(RUNDATE, -1)

    logging.info('onedayAgoDMS(): onedayAgo:%s', onedayAgo)

    olddmsDF = spark.table(WITHDB('dms_data')) \
                    .filter('vender_id='+VENDERID) \
                    .filter('dt='+onedayAgo) \
                    .withColumn('dms_old', F.col('dms')) \
                    .withColumn('dms_n_old', F.col('dms_n')) \
                    .withColumn('dms_p_old', F.col('dms_p')) \
                    .withColumn('yesterday_is_prom_old', F.col('yesterday_is_prom')) \
                    .select('mandt', 'werks', 'sku', 'dms_old', 'dms_n_old', 'dms_p_old', 'yesterday_is_prom_old')

    # NOTE: Spark限制不能Overwrite正在Read的表(保证数据一致性)
    #       这里我们引入中间表达到我们的目的
    tmpDmsDayVender = WITHDB('tmp_olddms_day_vender'+VENDERID)
    olddmsDF.dropDuplicates(['mandt', 'werks', 'sku']) \
            .write \
            .mode('overwrite') \
            .saveAsTable(tmpDmsDayVender)

    return spark.table(tmpDmsDayVender)


def saleFlag():
    """最近一年门店商品销售记录flag"""

    onedayAgo = datediff(RUNDATE, -1)
    yearAgo = datediff(onedayAgo, -365)

    logging.info('saleFlag(): onedayAgo:%s, yearAgo:%s', onedayAgo, yearAgo)

    # 门店
    storeDF = spark.table('dm_data.dim_store') \
                   .filter('store_test_flag != 2') \
                   .filter('store_sap_id not like "DC%"') \
                   .withColumn('mandt', F.col('vender_sap_id')) \
                   .withColumn('werks', F.col('store_sap_id')) \
                   .select('vender_id', 'mandt', 'store_id', 'werks') \
                   .dropDuplicates(['vender_id', 'store_id'])

    # 线下销售
    offlineDF = spark.table('dwd_data.dwd_order_offline_ware') \
                     .filter('dt >= '+yearAgo) \
                     .filter('dt <= '+onedayAgo) \
                     .filter('ware_num > 0.0') \
                     .filter('order_complete_status = 1024') \
                     .filter('vender_id = '+VENDERID) \
                     .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                     .withColumn('date', F.col('dt')) \
                     .withColumn('salequantity', F.col('ware_num').astype(FloatType())) \
                     .select('vender_id', 'store_id', 'sku', 'date')

    offlineStoreDF = fastjoin(offlineDF, storeDF, ['store_id', 'vender_id'], 'inner').select('mandt', 'werks', 'sku').distinct()

    # 自由购（线上）销售
    freegoDF = spark.table('dwd_data.dwd_order_freego_ware') \
                    .filter('dt >= '+yearAgo) \
                    .filter('dt <= '+onedayAgo) \
                    .filter('ware_num > 0.0') \
                    .filter('order_complete_status = 1024') \
                    .filter('vender_id = '+VENDERID) \
                    .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                    .withColumn('date', F.col('dt')) \
                    .withColumn('salequantity', F.col('ware_num').astype(FloatType())) \
                    .select('vender_id', 'store_id', 'sku', 'date')

    freegoStoreDF = fastjoin(freegoDF, storeDF, ['store_id', 'vender_id'], 'inner').select('mandt', 'werks', 'sku').distinct()

    # 线下和自由购(线上)合并
    saleDF = safeunion(offlineStoreDF, freegoStoreDF).distinct()

    saleDF = saleDF.withColumn('sale_flag', F.lit(1))

    tmpSaleFlagTable = 'tmp_sale_flag'

    saleDF.write \
          .mode('overwrite') \
          .saveAsTable(WITHDB(tmpSaleFlagTable))

    saleDF.unpersist()

    logging.info('saleFlag(): tmpSaleFlagTable:%s', WITHDB(tmpSaleFlagTable))

    return spark.table(WITHDB(tmpSaleFlagTable))


def promoStatus():
    """昨天、今天门店商品促销状态"""

    # 档期时间范围 [now()-40d, now()+20d]
    day40Before = datediff(RUNDATE, -40)
    day20After = datediff(RUNDATE, +20)

    logging.info('promoStatus(): day40Before:%s, day20After:%s', day40Before, day20After)

    # 门店促销信息（全量表）
    siteDF = spark.table(WITHDB('etl_promoplanitemsite_sigma')) \
                  .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                  .filter('({0}<=vkdab and vkdab<={1}) or ({0}<=vkdbi and vkdbi<={1})'.format(day40Before, day20After)) \
                  .select('mandt', 'werks', 'sku', 'ref_promo', 'aktnr', 'vkdab', 'vkdbi')

    # 商品促销信息（全量表）
    itemDF = spark.table(WITHDB('etl_promoplanitem_sigma')) \
                  .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                  .filter('pstop != "X"') \
                  .select('mandt', 'ref_promo', 'aktnr', 'sku')

    promoDF = fastjoin(siteDF, itemDF, ['mandt', 'ref_promo', 'aktnr', 'sku']).select('mandt',
                                                                                      'werks',
                                                                                      'sku',
                                                                                      'ref_promo',
                                                                                      'aktnr',
                                                                                      'vkdab',
                                                                                      'vkdbi')

    promoDF = promoDF.groupBy('mandt', 'werks', 'sku', 'ref_promo') \
                     .agg(F.collect_list(F.array('vkdab', 'vkdbi')).alias('aktnr_list'))

    promoDF = promoDF.groupBy('mandt', 'werks', 'sku') \
                     .agg(F.collect_list('aktnr_list').alias('promo_list'))

    def pstatus(promo_list):
        yesterday = datediff(RUNDATE, -1)
        yesterdayIsPromStart, yesterdayIsProm, todayIsPromStart = 0, 0, 0
        for aktnr_list in promo_list:
            aktnr_list.sort()
            for aktnr in aktnr_list:
                assert len(aktnr) == 2, 'want:tuple(vkdab, vkdbi), have:%s' % aktnr
                begin, end = aktnr[0], aktnr[1]
                if begin <= yesterday and yesterday <= end:
                    yesterdayIsProm = 1
                if begin == yesterday:
                    yesterdayIsPromStart = 1
                if begin == RUNDATE:
                    todayIsPromStart = 1
        return (yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart)

    pstatusFunc = F.udf(pstatus, ArrayType(IntegerType(), False))

    promoDF = promoDF.withColumn('p_status', pstatusFunc('promo_list')) \
                     .drop('promo_list')

    tmpPromoStatusTable = 'tmp_promo_status'

    promoDF.write \
           .mode('overwrite') \
           .saveAsTable(WITHDB(tmpPromoStatusTable))

    promoDF.unpersist()

    logging.info('promoStatus(): tmpPromoStatusTable:%s', WITHDB(tmpPromoStatusTable))

    return spark.table(WITHDB(tmpPromoStatusTable))


def confRate():
    # Json模板：lib/dms-conf-template.json
    DEFAULT_CONF_VALS = CONFJSON['defaultParamWeight']
    assert len(DEFAULT_CONF_VALS) == 5, 'exactly 5 KVs expected'
    DEFAULT_RATE_MAP = {}
    for confVal in DEFAULT_CONF_VALS:
        typ = confVal['type']
        saleRate = confVal['yesterdayScalWeight']
        dmsRate = confVal['historyScalWeight']
        DEFAULT_RATE_MAP[typ] = {'salerate': saleRate, 'dmsrate': dmsRate}

    DEFAULT_RATE_ARRAY = [
        DEFAULT_RATE_MAP['firstScheduledayPromotiongoods']['salerate'],  # 0: 促销品开档日销量占比
        DEFAULT_RATE_MAP['firstScheduledayPromotiongoods']['dmsrate'],   # 1: 促销品开档日DMS占比

        DEFAULT_RATE_MAP['holidayPromotiongoods']['salerate'],           # 2: 促销品节假日销量占比
        DEFAULT_RATE_MAP['holidayPromotiongoods']['dmsrate'],            # 3: 促销品节假日DMS占比

        DEFAULT_RATE_MAP['weekdayPromotiongoods']['salerate'],           # 4: 促销品工作日销量占比
        DEFAULT_RATE_MAP['weekdayPromotiongoods']['dmsrate'],            # 5: 促销品工作日DMS占比

        DEFAULT_RATE_MAP['holidayNormalgoods']['salerate'],              # 6: 正常品节假日销量占比
        DEFAULT_RATE_MAP['holidayNormalgoods']['dmsrate'],               # 7: 正常品节假日DMS占比

        DEFAULT_RATE_MAP['weekdayNormalgoods']['salerate'],              # 8: 正常品工作日销量占比
        DEFAULT_RATE_MAP['weekdayNormalgoods']['dmsrate'],               # 9: 正常品工作日DMS占比
    ]

    logging.info('confRate(): DEFAULT_RATE_ARRAY:%s', DEFAULT_RATE_ARRAY)

    datalist = []
    WERKS_BIGCLASS_WEIGHTS = CONFJSON['paramWeights']
    for werksBigClassWeight in WERKS_BIGCLASS_WEIGHTS:
        werks = werksBigClassWeight['shopCode']
        bigClass = werksBigClassWeight['categoryId']
        confValList = werksBigClassWeight['jsonValue']
        if werks is None or bigClass is None or confValList is None:
            logging.warning('confRate(): null value: werks:%s, big_class:%s, jsonValue:%s', werks, bigClass, confValList)
            continue

        logging.info('confRate(): werks:%s, big_class:%s', werks, bigClass)
        assert len(confValList) == 5, 'exactly 5 KVs expected'
        rateMap = {}
        for confVal in confValList:
            typ = confVal['type']
            saleRate = confVal['yesterdayScalWeight']
            dmsRate = confVal['historyScalWeight']
            rateMap[typ] = {'salerate': saleRate, 'dmsrate': dmsRate}
            logging.info('confRate():  typ:%s, saleRate:%s, dmsRate:%s', typ, saleRate, dmsRate)
        # NOTE: 为了在Hive表存储复杂的Python对象，这里序列化成String
        rateMapStr = json.dumps(rateMap)
        datalist.append((werks, bigClass, rateMapStr))

    # [STRING]: conf_rate:
    # {
    #     "weekdayNormalgoods" : {
    #         "salerate" : 0.2,
    #         "dmsrate" : 0.8
    #     },
    #     "weekdayPromotiongoods" : {
    #         "salerate" : 0.5,
    #         "dmsrate" : 0.5
    #     },
    #     "holidayNormalgoods" : {
    #         "salerate" : 0.3,
    #         "dmsrate" : 0.7
    #     },
    #     "holidayPromotiongoods": {
    #         "salerate" : 0.1,
    #         "dmsrate" : 0.9
    #     },
    #     "firstScheduledayPromotiongoods": {
    #         "salerate" : 0.2,
    #         "dmsrate" : 0.8
    #     }
    # }
    werksBigClassRateDF = spark.createDataFrame(spark.sparkContext.parallelize(datalist),
                                                ('werks', 'big_class', 'conf_rate'))

    # https://spark.apache.org/docs/2.1.1/api/python/pyspark.sql.html#pyspark.sql.functions.get_json_object
    # NOTE: F.get_json_object()函数返回值为String类型
    werksBigClassRateDF = werksBigClassRateDF.withColumn('conf_rate_array',
                                                         F.array(F.get_json_object('conf_rate', '$.firstScheduledayPromotiongoods.salerate'),   # 0: 促销品开档日销量占比
                                                                 F.get_json_object('conf_rate', '$.firstScheduledayPromotiongoods.dmsrate'),    # 1: 促销品开档日DMS占比
                                                                 F.get_json_object('conf_rate', '$.holidayPromotiongoods.salerate'),            # 2: 促销品节假日销量占比
                                                                 F.get_json_object('conf_rate', '$.holidayPromotiongoods.dmsrate'),             # 3: 促销品节假日DMS占比
                                                                 F.get_json_object('conf_rate', '$.weekdayPromotiongoods.salerate'),            # 4: 促销品工作日销量占比
                                                                 F.get_json_object('conf_rate', '$.weekdayPromotiongoods.dmsrate'),             # 5: 促销品工作日DMS占比
                                                                 F.get_json_object('conf_rate', '$.holidayNormalgoods.salerate'),               # 6: 正常品节假日销量占比
                                                                 F.get_json_object('conf_rate', '$.holidayNormalgoods.dmsrate'),                # 7: 正常品节假日DMS占比
                                                                 F.get_json_object('conf_rate', '$.weekdayNormalgoods.salerate'),               # 8: 正常品工作日销量占比
                                                                 F.get_json_object('conf_rate', '$.weekdayNormalgoods.dmsrate')))               # 9: 正常品工作日DMS占比

    tmpConfTable = 'tmp_dms_conf_parsed'

    werksBigClassRateDF.write \
                       .mode('overwrite') \
                       .saveAsTable(WITHDB(tmpConfTable))

    werksBigClassRateDF.unpersist()

    logging.info('confRate(): tmpConfTable:%s', WITHDB(tmpConfTable))

    return (spark.table(WITHDB(tmpConfTable)), DEFAULT_RATE_ARRAY)


def dms():
    onedayAgo = datediff(RUNDATE, -1)
    twodayAgo = datediff(RUNDATE, -2)

    logging.info('dms(): onedayAgo:%s, twodayAgo:%s', onedayAgo, twodayAgo)

    # 商品主数据表（所有门店所有商品）
    articleDF = spark.table(WITHDB('m_sitearticle')) \
                     .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                     .withColumn('status', F.col('mmsta')) \
                     .filter('werks not like "%DC%"') \
                     .filter(F.col('sku').isNotNull()) \
                     .filter('mandt='+MANDT) \
                     .select('mandt', 'werks', 'sku', 'status') \
                     .dropDuplicates(['mandt', 'werks', 'sku'])

    onedayAgoDmsDF = onedayAgoDMS()

    dmsDF = fastjoin(articleDF, onedayAgoDmsDF, ['mandt', 'werks', 'sku'], 'left').fillna(0.0) \
                                                                                  .select('mandt',
                                                                                          'werks',
                                                                                          'sku',
                                                                                          'status',
                                                                                          'dms_old',
                                                                                          'dms_n_old',
                                                                                          'dms_p_old',
                                                                                          'yesterday_is_prom_old')

    # 昨日销量（已清洗）
    daysaleDF = spark.table(WITHDB('clean_order')) \
                     .filter('dt = '+onedayAgo) \
                     .filter('clean_flag = "ALL_PASSED"') \
                     .filter('vender_id = '+VENDERID) \
                     .groupBy('mandt', 'werks', 'sku') \
                     .agg(F.sum('salequantity').alias('sale'))

    dmsDF = fastjoin(dmsDF, daysaleDF, ['mandt', 'werks', 'sku'], 'left').fillna({'sale': 0.0})

    promDF = promoStatus()

    # Join促销
    dmsDF = fastjoin(dmsDF, promDF, ['mandt', 'werks', 'sku'], 'left')

    # 库存
    # NOTE: 使用销售当日(onedayAgo)开始库存，即前天(twodayAgo)的日结库存
    stockDF = spark.table(WITHDB('ods_zscmexc')) \
                   .filter('dt = '+twodayAgo) \
                   .filter('mandt = '+MANDT) \
                   .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                   .withColumn('stock', F.col('labst').astype(FloatType())) \
                   .select('mandt', 'werks', 'sku', 'stock') \
                   .dropDuplicates(['mandt', 'werks', 'sku', 'stock'])

    # Join库存
    dmsDF = fastjoin(dmsDF, stockDF, ['mandt', 'werks', 'sku'], 'left').fillna({'stock': 0.0})

    # Join过去一年是否有过销售记录(0:无 1:有)
    saleflagDF = saleFlag()
    dmsDF = fastjoin(dmsDF, saleflagDF, ['mandt', 'werks', 'sku'], 'left').fillna({'sale_flag': 0})

    dmsDF = dmsDF.select('mandt',
                         'werks',
                         'sku',
                         'status',
                         'sale_flag',
                         'dms_old',
                         'dms_n_old',
                         'dms_p_old',
                         'yesterday_is_prom_old',
                         'p_status',
                         'sale',
                         'stock')

    # 销量当天(昨日onedayAgo)是否节假日
    if isChinaHoliday(onedayAgo):
        date_type = 1
    else:
        date_type = 0
    dmsDF = dmsDF.withColumn('date_type', F.lit(date_type))

    # 符合计算DMS的商品状态
    STATUS_DMS = CONFJSON['goodsStatus']
    logging.info('dms(): STATUS_DMS:%s', STATUS_DMS)

    # Join供商配置比例
    werksBigClassRateDF, DEFAULT_RATE_ARRAY = confRate()
    logging.info('dms(): DEFAULT_RATE_ARRAY:%s', DEFAULT_RATE_ARRAY)

    classDF = spark.table(WITHDB('etl_class')).select('big_class', 'sku').dropDuplicates(['sku'])

    dmsDF = fastjoin(dmsDF, classDF, ['sku'], 'left')

    dmsDF = fastjoin(dmsDF, werksBigClassRateDF, ['werks', 'big_class'], 'left')

    def dmscalc(status, sale_flag, dms_old, dms_n_old, dms_p_old, p_status, sale, stock, yesterday_is_prom_old, date_type, conf_rate_array):
        salerate, olddmsrate = 0.0, 0.0
        dms_today, dms_n_today, dms_p_today = 0.0, 0.0, 0.0
        yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart = 0, 0, 0

        if p_status is not None:
            assert len(p_status) == 3, 'want:tuple(yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart), have:%s' % p_status
            yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart = p_status[0], p_status[1], p_status[2]

        # 过去一年商品没有销售记录(0:无 1:有)
        if sale_flag == 0:
            return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

        # 商品状态不需要计算DMS,取昨日值
        status = str(status).strip()
        if status not in STATUS_DMS:
            dms_n_today = dms_n_old
            dms_p_today = dms_p_old
            dms_today = dms_p_today if yesterdayIsProm else dms_n_today
            return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

        # 3个条件同时满足的情况下，商品不需要计算DMS,取昨日值
        #  1) 昨天和前天促销状态一样(都是促销或者都是非促销)
        #  2) 昨日的初始库存小于等于前天dms值的1/4(0.25)
        #  3) 今天不是促销开始
        if yesterdayIsProm == yesterday_is_prom_old and stock <= 0.25*dms_old and todayIsPromStart != 1:
            dms_n_today = dms_n_old
            dms_p_today = dms_p_old
            dms_today = dms_p_today if yesterdayIsProm else dms_n_today
            return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

        # conf_rate_array: [
        #     0: 促销品开档日(销量占比)
        #     1: 促销品开档日(DMS占比)
        #
        #     2: 促销品节假日(销量占比)
        #     3: 促销品节假日(DMS占比)
        #
        #     4: 促销品工作日(销量占比)
        #     5: 促销品工作日(DMS占比)
        #
        #     6: 正常品节假日(销量占比)
        #     7: 正常品节假日(DMS占比)
        #
        #     8: 正常品工作日(销量占比)
        #     9: 正常品工作日(DMS占比)
        # ]
        if conf_rate_array is None:
            conf_rate_array = DEFAULT_RATE_ARRAY
        assert len(conf_rate_array) == 10, 'Why len != 10? conf_rate_array:%s' % conf_rate_array
        conf_rate_array = [float(rate) for rate in conf_rate_array]

        #
        # 促销品
        #
        if yesterdayIsPromStart:
            # 开档日
            salerate = conf_rate_array[0]
            olddmsrate = conf_rate_array[1]
            dms_p_today = sale*salerate + dms_n_old*olddmsrate
            dms_n_today = dms_n_old
            dms_today = dms_p_today
            return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

        #
        # 促销品
        #
        if yesterdayIsProm:
            if date_type == 1:
                # 节假日
                salerate = conf_rate_array[2]
                olddmsrate = conf_rate_array[3]
            else:
                # 工作日
                salerate = conf_rate_array[4]
                olddmsrate = conf_rate_array[5]
            dms_p_today = sale*salerate + dms_p_old*olddmsrate
            dms_n_today = dms_n_old
            dms_today = dms_p_today
            return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

        #
        # 正常品
        #
        if date_type == 1:
            # 节假日
            salerate = conf_rate_array[6]
            olddmsrate = conf_rate_array[7]
        else:
            # 工作日
            salerate = conf_rate_array[8]
            olddmsrate = conf_rate_array[9]
        dms_n_today = sale*salerate + dms_n_old*olddmsrate
        dms_p_today = dms_p_old
        dms_today = dms_n_today
        return (dms_today, dms_n_today, dms_p_today, yesterdayIsProm, yesterdayIsPromStart, todayIsPromStart, salerate, olddmsrate, date_type)

    dmsSchema = StructType([StructField('dms', FloatType()),
                            StructField('dms_n', FloatType()),
                            StructField('dms_p', FloatType()),
                            StructField('yesterday_is_prom', IntegerType()),
                            StructField('yesterday_is_prom_start', IntegerType()),
                            StructField('today_is_prom_start', IntegerType()),
                            StructField('salerate', FloatType()),
                            StructField('olddmsrate', FloatType()),
                            StructField('date_type', IntegerType())])

    dmscalcFunc = F.udf(dmscalc, dmsSchema)

    dmsDF = dmsDF.withColumn('dms_infos', dmscalcFunc('status',
                                                      'sale_flag',
                                                      'dms_old',
                                                      'dms_n_old',
                                                      'dms_p_old',
                                                      'p_status',
                                                      'sale',
                                                      'stock',
                                                      'yesterday_is_prom_old',
                                                      'date_type',
                                                      'conf_rate_array'))

    dmsDF = dmsDF.withColumn('dms', F.col('dms_infos').getItem('dms')) \
                 .withColumn('dms_n', F.col('dms_infos').getItem('dms_n')) \
                 .withColumn('dms_p', F.col('dms_infos').getItem('dms_p')) \
                 .withColumn('yesterday_is_prom', F.col('dms_infos').getItem('yesterday_is_prom')) \
                 .withColumn('yesterday_is_prom_start', F.col('dms_infos').getItem('yesterday_is_prom_start')) \
                 .withColumn('today_is_prom_start', F.col('dms_infos').getItem('today_is_prom_start')) \
                 .withColumn('salerate', F.col('dms_infos').getItem('salerate')) \
                 .withColumn('olddmsrate', F.col('dms_infos').getItem('olddmsrate')) \
                 .withColumn('date_type', F.col('dms_infos').getItem('date_type'))

    dmsDF = dmsDF.select('mandt',
                         'werks',
                         'sku',
                         'dms',
                         'dms_n',
                         'dms_p',
                         'status',
                         'sale_flag',
                         'dms_old',
                         'dms_n_old',
                         'dms_p_old',
                         'yesterday_is_prom',
                         'yesterday_is_prom_start',
                         'today_is_prom_start',
                         'sale',
                         'stock',
                         'salerate',
                         'olddmsrate',
                         'date_type')

    # Save hive with partition
    dmsDF = dmsDF.withColumn('vender_id', F.lit(VENDERID)) \
                 .withColumn('dt', F.lit(RUNDATE))

    savehive(dmsDF,
             ['vender_id', 'dt'],
             'vender_id="{0}", dt="{1}"'.format(VENDERID, RUNDATE),
             WITHDB('dms_data'))


def isChinaHoliday(datestr):
    year = datestr[0:4]  # fmt:20180425
    holidayDataList = spark.table(WITHDB('dms_holiday')) \
                           .filter('year='+year) \
                           .take(1)

    assert len(holidayDataList) == 1, 'Why table:%s year:%s no data?' % (WITHDB('dms_holiday'), year)

    holidayData = holidayDataList[0]
    originJson, year = holidayData['origin_json'], holidayData['year']

    logging.info('isChinaHoliday(): year:%s', year)
    logging.info('isChinaHoliday(): originJson:\n%s', jsonpretty(originJson))

    # Json模板：lib/dms-holiday-template.json
    holidayJson = json.loads(originJson)

    HolidayHappy = holidayJson['holidayhappy']  # 国家法定假日
    HolidayCry = holidayJson['holidaycry']      # 周末因法定假日上班

    if datestr in HolidayHappy:
        logging.info('isChinaHoliday(): %s in HolidayHappy', datestr)
        return True

    if datestr in HolidayCry:
        logging.info('isChinaHoliday(): %s in HolidayCry', datestr)
        return False

    # 正常周末放假
    d = datetime.datetime.strptime(datestr, '%Y%m%d')
    wd = d.isoweekday()
    logging.info('isChinaHoliday(): %s is week %s', datestr, wd)
    if wd in [6, 7]:
        return True

    return False


def dmsconf():
    # 取最近时间供商配置数据
    confDataList = spark.table(WITHDB('dms_conf')) \
                        .orderBy('dt', ascending=False) \
                        .take(1)

    assert len(confDataList) == 1, 'Why table:%s is empty?' % WITHDB('dms_conf')

    confData = confDataList[0]
    originJson, date = confData['origin_json'], confData['dt']

    logging.info('dmsconf(): date:%s', date)
    logging.info('dmsconf(): originJson:\n%s', jsonpretty(originJson))

    # Json模板: lib/dms-conf-template.json
    return (json.loads(originJson), date)


if __name__ == '__main__':
    logging.info('start dms')

    RUNDATE = datenow()
    CONFJSON, CONFDATE = dmsconf()

    dms()
    logging.info('finish dms')
    spark.stop()
