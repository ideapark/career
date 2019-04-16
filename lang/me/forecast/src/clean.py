#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 数据清洗(CLEAN)
#
# clean_1: if 小票数量>=X(X=5),if 门店小票最大值No.1/门店小票第二大值No.2>Y，并且
#          Z表示最近半年销量中位数,当Y和Z满足如下任一关系时，将小票最大值No.1清除:
#            1) Z∊[-inf, 10] && Y>5
#            2) Z∊[10,   20] && Y>4
#            3) Z∊[30, +inf] && Y>3
#          代码实现参考函数：def testkickout()
#
# clean_2: if 小票数量<X(X=5)，将该门店所属的门店类（例如A类）中所有该sku的当日小票综合到一起形成U：
#
#     clean_2_1: if U中小票数>=X(X=5),按照clean-1清理
#
#     clean_2_2: if 小票数量<X(X=5),将U的取数范围扩展为门店类最近一周的所有小票,按照clean_1清理
#
#     clean_2_3: if 小票数量<X(X=5),则不做处理
#
# clean_3: 完成clean_1和clean_2后,过去半年的销量中位数(假设为Y),清除小票如果小票销量大于N_MEDIAN倍Y
#          (N_MEDIAN在物美默认值20,供商独立可以配置)
#
# 清理标记:
#
#   clean_1: 小票被规则一清洗
#   clean_2: 小票被规则二清洗
#   clean_3: 小票被规则三清洗
#   ... ...
#   ALL_PASSED: 通过所有清洗规则

import json
import logging
import datetime
import numpy as np
import pyspark.sql.functions as F
from pyspark.sql import SparkSession
from pyspark.sql.types import IntegerType, FloatType, StringType
from pyspark.sql.types import ArrayType, StructType, StructField

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::clean") \
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


def daycount(datestart, dateend):
    """
    daycount() returns how many days between datestart and dateend,
    args sequence does not matter, we have protection against such
    situation.
    """
    s = datetime.datetime.strptime(datestart, '%Y%m%d')
    e = datetime.datetime.strptime(dateend, '%Y%m%d')
    return abs((e-s).days)+1  # off by 1


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


def prepareDF(startDate, endDate):
    assert startDate <= endDate, 'startDate:%s must <= endDate:%s' % (startDate, endDate)

    logging.info('prepareDF(): startDate:%s, endDate:%s', startDate, endDate)

    # 门店促销信息（全量表）
    siteDF = spark.table(WITHDB('etl_promoplanitemsite_sigma')) \
                  .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                  .filter('({0} <= vkdab and vkdab <= {1}) or ({0} <= vkdbi and vkdbi <= {1})'.format(startDate, endDate)) \
                  .select('mandt', 'werks', 'sku', 'ref_promo', 'aktnr', 'vkdab', 'vkdbi')

    # 商品促销信息（全量表）
    itemDF = spark.table(WITHDB('etl_promoplanitem_sigma')) \
                  .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                  .filter('pstop != "X"') \
                  .select('mandt', 'ref_promo', 'aktnr', 'sku') \
                  .dropDuplicates(['mandt', 'ref_promo', 'aktnr', 'sku'])

    promoDF = fastjoin(siteDF, itemDF, ['mandt', 'ref_promo', 'aktnr', 'sku']).select('mandt',
                                                                                      'werks',
                                                                                      'sku',
                                                                                      'ref_promo',
                                                                                      'aktnr',
                                                                                      'vkdab',
                                                                                      'vkdbi')

    # 展开促销周期的每一天
    def expandDays(vkdab, vkdbi):
        assert vkdab <= vkdbi, 'vkdab:%s must <= vkdbi:%s' % (vkdab, vkdbi)
        start, end = vkdab, vkdbi
        s = datetime.datetime.strptime(start, '%Y%m%d')
        e = datetime.datetime.strptime(end, '%Y%m%d')
        dateIsPromo = [datediff(start, +n) for n in range((e-s).days+1)]
        return dateIsPromo

    expandDaysFunc = F.udf(expandDays, ArrayType(StringType(), False))

    promoDF = promoDF.select(F.col('mandt'),
                             F.col('werks'),
                             F.col('sku'),
                             F.explode(expandDaysFunc('vkdab', 'vkdbi')).alias('date')).distinct()
    promoDF = promoDF.withColumn('promo_label', F.lit(1))

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
                     .filter('dt >= '+startDate) \
                     .filter('dt <= '+endDate) \
                     .filter('ware_num > 0.0') \
                     .filter('order_complete_status = 1024') \
                     .filter('vender_id = '+VENDERID) \
                     .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                     .withColumn('date', F.col('dt')) \
                     .withColumn('salequantity', F.col('ware_num').astype(FloatType())) \
                     .withColumn('saledt', F.col('order_complete_time')) \
                     .withColumn('saleamt', ((F.col('ware_num')*F.col('ware_price')-F.col('promotion_price'))/F.lit(100.0)).astype(FloatType())) \
                     .select('vender_id', 'store_id', 'sku', 'date', 'salequantity', 'pos_order_sn', 'saledt', 'saleamt')

    offlineStoreDF = fastjoin(offlineDF, storeDF, ['store_id', 'vender_id']).select('mandt',
                                                                                    'werks',
                                                                                    'sku',
                                                                                    'date',
                                                                                    'salequantity',
                                                                                    'pos_order_sn',
                                                                                    'saledt',
                                                                                    'saleamt')

    # 自由购（线上）销售
    freegoDF = spark.table('dwd_data.dwd_order_freego_ware') \
                    .filter('dt >= '+startDate) \
                    .filter('dt <= '+endDate) \
                    .filter('ware_num > 0.0') \
                    .filter('order_complete_status = 1024') \
                    .filter('vender_id = '+VENDERID) \
                    .withColumn('sku', F.col('matnr').astype(IntegerType())) \
                    .withColumn('date', F.col('dt')) \
                    .withColumn('salequantity', F.col('ware_num').astype(FloatType())) \
                    .withColumn('saledt', F.col('order_complete_time')) \
                    .withColumn('saleamt', ((F.col('ware_num')*F.col('ware_price')-F.col('promotion_price'))/F.lit(100.0)).astype(FloatType())) \
                    .withColumn('pos_order_sn', F.col('order_id')) \
                    .select('vender_id', 'store_id', 'sku', 'date', 'salequantity', 'pos_order_sn', 'saledt', 'saleamt')

    freegoStoreDF = fastjoin(freegoDF, storeDF, ['store_id', 'vender_id']).select('mandt',
                                                                                  'werks',
                                                                                  'sku',
                                                                                  'date',
                                                                                  'salequantity',
                                                                                  'pos_order_sn',
                                                                                  'saledt',
                                                                                  'saleamt')

    # 线下和自由购(线上)销量合并
    saleDF = safeunion(offlineStoreDF, freegoStoreDF)

    # 销量表是否促销标记
    saleDF = fastjoin(saleDF, promoDF, ['mandt', 'werks', 'sku', 'date'], 'left').fillna({'promo_label': 0})

    # NOTE: 这里发生过sku为null导致程序崩溃(有脏数据?)
    saleDF = saleDF.filter(F.col('sku').isNotNull()) \
                   .filter(F.col('werks').isNotNull())

    logging.info('prepareDF: startDate:%s, endDate:%s, count:%s', startDate, endDate, saleDF.count())

    # NOTE: Copy原始销量值,清洗过程中销量可能被修正
    return saleDF.select('mandt',
                         'werks',
                         'sku',
                         'date',
                         'promo_label',
                         'salequantity',
                         'pos_order_sn',
                         'saledt',
                         'saleamt').withColumn('raw_qty', F.col('salequantity')).cache()


def testkickout(ratio, qty_median):
    qtyratio_table = [
        # qty_min      qty_max        ratio_max
        (float('-inf'), 10.0,          5.0),
        (10.0,          20.0,          4.0),
        (20.0,          30.0,          3.0),
        (30.0,          float('+inf'), 2.0),
    ]
    for qtyratio in qtyratio_table:
        qty_min, qty_max, ratio_max = qtyratio[0], qtyratio[1], qtyratio[2]
        if qty_min < qty_median and qty_median <= qty_max:
            if ratio > ratio_max:
                return True
    return False


def clean_1(saleDF):
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('clean_1(): onedayAgo:%s', onedayAgo)

    def order(salequantity, raw_qty, pos_order_sn, saleamt, saledt):
        return (salequantity, raw_qty, pos_order_sn, saleamt, saledt)

    orderSchema = StructType([StructField('salequantity', FloatType()),
                              StructField('raw_qty', FloatType()),
                              StructField('pos_order_sn', StringType()),
                              StructField('saleamt', FloatType()),
                              StructField('saledt', StringType())])

    orderFunc = F.udf(order, orderSchema)

    orderDF = saleDF.withColumn('order', orderFunc('salequantity', 'raw_qty', 'pos_order_sn', 'saleamt', 'saledt')) \
                    .groupBy('mandt', 'werks', 'sku', 'date', 'promo_label') \
                    .agg(F.collect_list('order').alias('order_list'))

    medianDF = spark.table(WITHDB('preprocess_sixmonth')) \
                    .filter('dt='+onedayAgo) \
                    .filter('vender_id='+VENDERID) \
                    .withColumn('promo_label', F.when(F.col('type') == 'normal', 0).otherwise(1)) \
                    .select('mandt', 'werks', 'sku', 'promo_label', 'qty_median')

    # Join半年的销量中位数
    orderDF = fastjoin(orderDF, medianDF, ['mandt', 'werks', 'sku', 'promo_label'], 'left').fillna({'qty_median': 1.0})

    def split(order_list, qty_median):
        assert len(order_list) >= N_ORDERS, 'order list length: want:>=%s, have:%s' % (N_ORDERS, len(order_list))
        order_list.sort(reverse=True)
        orderNo1, orderNo2 = order_list[0], order_list[1]
        sqty1, sqty2 = orderNo1['salequantity'], orderNo2['salequantity']
        ratio = float(sqty1)/float(sqty2)
        if not testkickout(ratio, qty_median):
            return (order_list, None)
        # 剔除No.1
        return (order_list[1:], order_list[0:1])

    splitFunc = F.udf(split, StructType([StructField('pass_order_list', ArrayType(orderSchema)),
                                         StructField('reject_order_list', ArrayType(orderSchema))]))

    orderDF = orderDF.withColumn('split_order', splitFunc('order_list', 'qty_median'))

    passDF = orderDF.withColumn('pass_order_list', F.col('split_order').getItem('pass_order_list')) \
                    .select('mandt', 'werks', 'sku', 'date', 'promo_label', F.explode('pass_order_list').alias('order')) \
                    .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                    .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                    .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                    .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                    .withColumn('saledt', F.col('order').getItem('saledt')) \
                    .drop('order')

    rejectDF = orderDF.withColumn('reject_order_list', F.col('split_order').getItem('reject_order_list')) \
                      .select('mandt', 'werks', 'sku', 'date', 'promo_label', F.explode('reject_order_list').alias('order')) \
                      .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                      .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                      .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                      .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                      .withColumn('saledt', F.col('order').getItem('saledt')) \
                      .drop('order')

    return (passDF, rejectDF)


def clean_2(saleDF):
    classDF = spark.table(WITHDB('etl_class')).select('middle_class', 'sku')

    # FIXME(cou): 这里发生了小票商品在商品主数据表中没有记录，基础数据Bug?
    saleDF = fastjoin(saleDF, classDF, ['sku'])

    clusterDF = spark.table(WITHDB('preprocess_labelwerks')) \
                     .filter('vender_id='+VENDERID) \
                     .withColumn('promo_label', F.when(F.col('type') == 'normal', 0).otherwise(1)) \
                     .select('mandt', 'werks', 'middle_class', 'promo_label', 'label')

    # Join门店分类
    saleDF = fastjoin(saleDF, clusterDF, ['mandt', 'werks', 'middle_class', 'promo_label'], 'left').fillna({'label': 1}) \
                                                                                                   .select('mandt',
                                                                                                           'werks',
                                                                                                           'label',  # 门店分类标签
                                                                                                           'sku',
                                                                                                           'date',
                                                                                                           'promo_label',
                                                                                                           'salequantity',
                                                                                                           'raw_qty',
                                                                                                           'pos_order_sn',
                                                                                                           'saleamt',
                                                                                                           'saledt')

    # 按门店分类统计订单数
    countDF = saleDF.groupBy('mandt', 'label', 'sku', 'date', 'promo_label') \
                    .agg(F.count('*').alias('n_orders'))

    ge5 = countDF.filter('n_orders >='+str(N_ORDERS)).drop('n_orders')
    c21DF = fastjoin(saleDF, ge5, ['mandt', 'label', 'sku', 'date', 'promo_label']).select('mandt',
                                                                                           'werks',
                                                                                           'label',  # 门店分类标签
                                                                                           'sku',
                                                                                           'date',
                                                                                           'promo_label',
                                                                                           'salequantity',
                                                                                           'raw_qty',
                                                                                           'pos_order_sn',
                                                                                           'saleamt',
                                                                                           'saledt')

    pass21DF, reject21DF = clean_2_1(c21DF)

    logging.info('clean_2_1: origin:%s, pass:%s, reject:%s', c21DF.count(), pass21DF.count(), reject21DF.count())

    lt5 = countDF.filter('n_orders <'+str(N_ORDERS)).drop('n_orders')
    c22DF = fastjoin(saleDF, lt5, ['mandt', 'label', 'sku', 'date', 'promo_label']).select('mandt',
                                                                                           'werks',
                                                                                           'label',  # 门店分类标签
                                                                                           'sku',
                                                                                           'date',
                                                                                           'promo_label',
                                                                                           'salequantity',
                                                                                           'raw_qty',
                                                                                           'pos_order_sn',
                                                                                           'saleamt',
                                                                                           'saledt')

    pass22DF, reject22DF = clean_2_2(c22DF)

    logging.info('clean_2_2: origin:%s, pass:%s, reject:%s', c22DF.count(), pass22DF.count(), reject22DF.count())

    return (safeunion(pass21DF, pass22DF), safeunion(reject21DF, reject22DF))


def clean_2_1(saleDF):
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('clean_2_1(): onedayAgo:%s', onedayAgo)

    def order(salequantity, raw_qty, pos_order_sn, saleamt, saledt, werks):
        return (salequantity, raw_qty, pos_order_sn, saleamt, saledt, werks)

    orderSchema = StructType([StructField('salequantity', FloatType()),
                              StructField('raw_qty', FloatType()),
                              StructField('pos_order_sn', StringType()),
                              StructField('saleamt', FloatType()),
                              StructField('saledt', StringType()),
                              StructField('werks', StringType())])

    orderFunc = F.udf(order, orderSchema)

    c21DF = saleDF.withColumn('order', orderFunc('salequantity', 'raw_qty', 'pos_order_sn', 'saleamt', 'saledt', 'werks')) \
                  .groupBy('mandt', 'label', 'sku', 'date', 'promo_label') \
                  .agg(F.collect_list('order').alias('order_list'))

    medianDF = spark.table(WITHDB('preprocess_sixmonth')) \
                    .filter('dt='+onedayAgo) \
                    .filter('vender_id='+VENDERID) \
                    .withColumn('promo_label', F.when(F.col('type') == 'normal', 0).otherwise(1)) \
                    .groupBy('mandt', 'sku', 'promo_label') \
                    .agg(F.mean('qty_median').alias('qty_median')) \
                    .select('mandt', 'sku', 'promo_label', 'qty_median')

    # Join半年的销量中位数
    c21DF = fastjoin(c21DF, medianDF, ['mandt', 'sku', 'promo_label'], 'left').fillna({'qty_median': 1.0})

    def split(order_list, qty_median):
        assert len(order_list) >= N_ORDERS, 'order list length: want:>=%s, have:%s' % (N_ORDERS, len(order_list))
        order_list.sort(reverse=True)
        orderNo1, orderNo2 = order_list[0], order_list[1]
        sqty1, sqty2 = orderNo1['salequantity'], orderNo2['salequantity']
        ratio = float(sqty1)/float(sqty2)
        # 不做处理
        if not testkickout(ratio, qty_median):
            return (order_list, None)
        # 门店当日是否只有一笔小票
        werks, werksCnt, salearray = orderNo1['werks'], 0, []
        for order in order_list:
            salearray.append(float(order['salequantity']))
            if werks == order['werks']:
                werksCnt += 1
        # 剔除No.1
        if werksCnt > 1:
            return (order_list[1:], order_list[0:1])
        # 修正No.1销量
        modOrder = list(order_list[0])
        modOrder[0] = float(np.median(np.array(salearray)))
        order_list = [tuple(modOrder)] + order_list[1:]
        return (order_list, None)

    splitFunc = F.udf(split, StructType([StructField('pass_order_list', ArrayType(orderSchema)),
                                         StructField('reject_order_list', ArrayType(orderSchema))]))

    c21DF = c21DF.withColumn('split_order', splitFunc('order_list', 'qty_median'))

    passDF = c21DF.withColumn('pass_order_list', F.col('split_order').getItem('pass_order_list')) \
                  .select('mandt', 'sku', 'date', 'promo_label', F.explode('pass_order_list').alias('order')) \
                  .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                  .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                  .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                  .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                  .withColumn('saledt', F.col('order').getItem('saledt')) \
                  .withColumn('werks', F.col('order').getItem('werks')) \
                  .drop('order')

    rejectDF = c21DF.withColumn('reject_order_list', F.col('split_order').getItem('reject_order_list')) \
                    .select('mandt', 'sku', 'date', 'promo_label', F.explode('reject_order_list').alias('order')) \
                    .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                    .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                    .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                    .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                    .withColumn('saledt', F.col('order').getItem('saledt')) \
                    .withColumn('werks', F.col('order').getItem('werks')) \
                    .drop('order')

    return (passDF, rejectDF)


def clean_2_2(saleDF):
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('clean_2_2(): onedayAgo:%s', onedayAgo)

    def order(salequantity, raw_qty, pos_order_sn, saleamt, saledt, werks):
        return (salequantity, raw_qty, pos_order_sn, saleamt, saledt, werks)

    orderSchema = StructType([StructField('salequantity', FloatType()),
                              StructField('raw_qty', FloatType()),
                              StructField('pos_order_sn', StringType()),
                              StructField('saleamt', FloatType()),
                              StructField('saledt', StringType()),
                              StructField('werks', StringType())])

    orderFunc = F.udf(order, orderSchema)

    c22DF = saleDF.withColumn('order', orderFunc('salequantity', 'raw_qty', 'pos_order_sn', 'saleamt', 'saledt', 'werks')) \
                  .groupBy('mandt', 'label', 'sku', 'date', 'promo_label') \
                  .agg(F.collect_list('order').alias('order_list'))

    def split(order_list, order_cnt, qty_max, qty_median):
        assert len(order_list) < N_ORDERS, 'order list length: want:<%s, have:%s' % (N_ORDERS, len(order_list))
        # 不做处理
        if len(order_list)+order_cnt < N_ORDERS:
            return (order_list, None)
        if len(order_list) < 2:
            return (order_list, None)

        order_list.sort(reverse=True)
        orderNo1, orderNo2 = order_list[0], order_list[1]
        sqty1, sqty2 = orderNo1['salequantity'], orderNo2['salequantity']
        maxQty = max(sqty2, qty_max)
        ratio = float(sqty1)/float(maxQty)
        # 不做处理
        if not testkickout(ratio, qty_median):
            return (order_list, None)
        # 门店当日是否只有一笔小票
        werks, werksCnt = orderNo1['werks'], 0
        for order in order_list:
            if werks == order['werks']:
                werksCnt += 1
        # 剔除No.1
        if werksCnt > 1:
            return (order_list[1:], order_list[0:1])
        # 修正No.1销量
        modOrder = list(order_list[0])
        modOrder[0] = qty_median
        order_list = [tuple(modOrder)] + order_list[1:]
        return (order_list, None)

    splitFunc = F.udf(split, StructType([StructField('pass_order_list', ArrayType(orderSchema)),
                                         StructField('reject_order_list', ArrayType(orderSchema))]))

    # 最近一周的销量信息
    weekDF = spark.table(WITHDB('preprocess_oneweek')) \
                  .filter('dt='+onedayAgo) \
                  .filter('vender_id='+VENDERID) \
                  .select('mandt', 'sku', 'label', 'qty_median', 'order_cnt', 'qty_max', F.when(F.col('type') == 'normal', 0).otherwise(1).alias('promo_label'))

    c22DF = fastjoin(c22DF, weekDF, ['mandt', 'label', 'sku', 'promo_label'], 'left').select('mandt',
                                                                                             'sku',
                                                                                             'date',
                                                                                             'promo_label',
                                                                                             'order_list',
                                                                                             'qty_median',
                                                                                             'order_cnt',
                                                                                             'qty_max') \
                                                                                     .fillna({'qty_median': 1.0}) \
                                                                                     .fillna({'order_cnt': 1.0}) \
                                                                                     .fillna({'qty_max': 1.0})

    c22DF = c22DF.withColumn('split_order', splitFunc('order_list', 'order_cnt', 'qty_max', 'qty_median'))

    passDF = c22DF.withColumn('pass_order_list', F.col('split_order').getItem('pass_order_list')) \
                  .select('mandt', 'sku', 'date', 'promo_label', F.explode('pass_order_list').alias('order')) \
                  .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                  .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                  .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                  .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                  .withColumn('saledt', F.col('order').getItem('saledt')) \
                  .withColumn('werks', F.col('order').getItem('werks')) \
                  .drop('order')

    rejectDF = c22DF.withColumn('reject_order_list', F.col('split_order').getItem('reject_order_list')) \
                    .select('mandt', 'sku', 'date', 'promo_label', F.explode('reject_order_list').alias('order')) \
                    .withColumn('salequantity', F.col('order').getItem('salequantity')) \
                    .withColumn('raw_qty', F.col('order').getItem('raw_qty')) \
                    .withColumn('pos_order_sn', F.col('order').getItem('pos_order_sn')) \
                    .withColumn('saleamt', F.col('order').getItem('saleamt')) \
                    .withColumn('saledt', F.col('order').getItem('saledt')) \
                    .withColumn('werks', F.col('order').getItem('werks')) \
                    .drop('order')

    return (passDF, rejectDF)


# 单笔销量超过半年单笔销量中位数倍数
N_MEDIAN = 20.0


def confThreshold():
    N_MEDIAN = float(CONFJSON['defaultCleanThreshold'])

    logging.info('confThreshold(): N_MEDIAN:%s', N_MEDIAN)

    bigclassThresholdList = CONFJSON['cleanThreshold']
    datalist = []
    for bigclassThreshold in bigclassThresholdList:
        bigclass = bigclassThreshold['categoryId']
        threshold = bigclassThreshold['threshold']
        datalist.append((bigclass, threshold))

    logging.info('confThreshold(): [(big_class, threshold)]:%s', datalist)

    bigclassThresholdDF = spark.createDataFrame(datalist, ('big_class', 'threshold'))

    classDF = spark.table(WITHDB('etl_class')).dropDuplicates(['sku'])

    skuThresholdDF = fastjoin(classDF, bigclassThresholdDF, ['big_class']).select(F.col('sku'),
                                                                                  F.col('threshold'))
    return skuThresholdDF


def clean_3(saleDF):
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('clean_3(): onedayAgo:%s', onedayAgo)

    medianDF = spark.table(WITHDB('preprocess_sixmonth')) \
                    .filter('dt='+onedayAgo) \
                    .filter('vender_id='+VENDERID) \
                    .withColumn('promo_label', F.when(F.col('type') == 'normal', 0).otherwise(1)) \
                    .select('mandt', 'werks', 'sku', 'promo_label', 'qty_median')

    # Join半年的销量中位数
    saleDF = fastjoin(saleDF, medianDF, ['mandt', 'werks', 'sku', 'promo_label'], 'left').fillna({'qty_median': 1.0})

    # Join供商阈值配置
    thresholdDF = confThreshold()
    saleDF = fastjoin(saleDF, thresholdDF, ['sku'], 'left').fillna({'threshold': N_MEDIAN})

    saleDF = saleDF.withColumn('qty_threshold', F.col('qty_median')*F.col('threshold'))

    passDF = saleDF.filter('salequantity < qty_threshold').select('mandt',
                                                                  'werks',
                                                                  'sku',
                                                                  'date',
                                                                  'promo_label',
                                                                  'salequantity',
                                                                  'raw_qty',
                                                                  'pos_order_sn',
                                                                  'saledt',
                                                                  'saleamt')

    rejectDF = saleDF.filter('salequantity >= qty_threshold').select('mandt',
                                                                     'werks',
                                                                     'sku',
                                                                     'date',
                                                                     'promo_label',
                                                                     'salequantity',
                                                                     'raw_qty',
                                                                     'pos_order_sn',
                                                                     'saledt',
                                                                     'saleamt')

    return (passDF, rejectDF)


# 订单数（来客数/小票数）
N_ORDERS = 5


# 清洗数据流图
#
#             saleDF = Offline+Online
#            /      \
#           /        \
#          ↙          ↘
#   IF>=N_ORDERS   IF<N_ORDERS
#        |              |
#        ↓              ↓
#    clean_1()       clean_2()
#       /\             /\
#      /  \           /  \
#     ↙    ↘         ↙    ↘
# reject1  pass1  pass2  reject2
#             \     /
#              \   /
#               ↘ ↙
#            clean_3()
#               /\
#              /  \
#             ↙    ↘
#         pass3    reject3
#
# 清洗结果
#
#   AllPass   = pass3
#   AllReject = reject1 + reject2 + reject3
#
def clean():
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('clean(): onedayAgo:%s', onedayAgo)

    saleDF = prepareDF(onedayAgo, onedayAgo)

    countDF = saleDF.groupBy('mandt', 'werks', 'sku', 'date', 'promo_label') \
                    .agg(F.count('*').alias('n_orders'))

    # 清洗规则一
    ge5 = countDF.filter('n_orders >='+str(N_ORDERS)).drop('n_orders')
    c1DF = fastjoin(saleDF, ge5, ['mandt', 'werks', 'sku', 'date', 'promo_label'])
    c1Pass, c1Reject = clean_1(c1DF)
    c1Reject = c1Reject.withColumn('clean_flag', F.lit('clean_1'))
    logging.info('clean_1: origin:%d, pass:%d, reject:%d', c1DF.count(), c1Pass.count(), c1Reject.count())

    # 清洗规则二
    lt5 = countDF.filter('n_orders <'+str(N_ORDERS)).drop('n_orders')
    c2DF = fastjoin(saleDF, lt5, ['mandt', 'werks', 'sku', 'date', 'promo_label'])
    c2Pass, c2Reject = clean_2(c2DF)
    c2Reject = c2Reject.withColumn('clean_flag', F.lit('clean_2'))
    logging.info('clean_2: origin:%d, pass:%d, reject:%d', c2DF.count(), c2Pass.count(), c2Reject.count())

    # 清洗规则三
    c3DF = safeunion(c1Pass, c2Pass)
    c3Pass, c3Reject = clean_3(c3DF)
    c3Reject = c3Reject.withColumn('clean_flag', F.lit('clean_3'))
    logging.info('clean_3: origin:%d, pass:%d, reject:%d', c3DF.count(), c3Pass.count(), c3Reject.count())

    # Set clean_flag=ALL_PASSED when all clean rules passed
    allPass = c3Pass.withColumn('clean_flag', F.lit('ALL_PASSED'))
    allReject = safeunion(safeunion(c1Reject, c2Reject), c3Reject)

    # NOTE: Why union and save, not savehive() separately?
    #       See git commit log
    hiveDF = safeunion(allPass, allReject)

    hiveDF = hiveDF.withColumn('vender_id', F.lit(VENDERID)) \
                   .withColumn('dt', F.lit(onedayAgo))

    # FIXME: Why we select columns explicitly?
    #        See git commit log
    hiveDF = hiveDF.select('mandt',
                           'werks',
                           'sku',
                           'date',
                           'promo_label',
                           'salequantity',
                           'pos_order_sn',
                           'saleamt',
                           'saledt',
                           'raw_qty',
                           'clean_flag',
                           'vender_id',
                           'dt')

    savehive(hiveDF,
             ['vender_id', 'dt'],
             'vender_id="{0}", dt="{1}"'.format(VENDERID, onedayAgo),
             WITHDB('clean_order'))


def stats():
    onedayAgo = datediff(RUNDATE, -1)

    df = spark.table(WITHDB('clean_order')) \
              .filter('vender_id = '+VENDERID) \
              .filter('dt = '+onedayAgo)

    passDF = df.filter('clean_flag = "ALL_PASSED"')
    rejectDF = df.filter('clean_flag != "ALL_PASSED"')
    # NOTE: 浮点数不能直接比较相等
    modifiedDF = df.filter(F.abs(F.col('salequantity')-F.col('raw_qty')) > F.lit(0.001))

    totalCount = df.count()
    passCount = passDF.count()
    rejectCount = rejectDF.count()
    modifiedCount = modifiedDF.count()

    logging.info('stats(): total:%d, pass:%d, reject:%d', totalCount, passCount, rejectCount)
    logging.info('stats(): percent:%0.5f%%', 100.0*float(rejectCount)/float(totalCount))
    logging.info('stats(): modified:%d', modifiedCount)

    passCountDF = passDF.groupBy('sku').agg(F.count('*').alias('pass'))
    rejectCountDF = rejectDF.groupBy('sku').agg(F.count('*').alias('reject'))
    statsDF = fastjoin(passCountDF, rejectCountDF, ['sku'], 'outer').fillna({'pass': 0, 'reject': 0})

    classDF = spark.table(WITHDB('etl_class'))

    statsDF = fastjoin(statsDF, classDF, ['sku'], 'left')

    statsDF = statsDF.groupBy('big_class', 'middle_class', 'small_class') \
                     .agg(F.sum('pass').alias('pass'),
                          F.sum('reject').alias('reject'))

    # Save to hive with partition
    statsDF = statsDF.withColumn('vender_id', F.lit(VENDERID)) \
                     .withColumn('dt', F.lit(onedayAgo))

    savehive(statsDF,
             ['vender_id', 'dt'],
             'vender_id="{0}", dt="{1}"'.format(VENDERID, onedayAgo),
             WITHDB('clean_stats'))


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
    logging.info('start clean')

    RUNDATE = datenow()
    CONFJSON, CONFDATE = dmsconf()

    clean()
    stats()
    logging.info('finish clean')
    spark.stop()
