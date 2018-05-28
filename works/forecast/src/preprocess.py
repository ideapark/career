#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 数据预处理(PREPROCESS)
#
# 1. 将门店按中分类middle_class分组聚类:def labelWerks()
# 2. 计算最近半年的销量日均和销量中位数:def sixMonth()
# 3. 计算最近一周的销量中位数和销售金额:def oneWeek()

import logging
import datetime
import numpy as np
import pyspark.sql.functions as F
from pyspark.sql import SparkSession, Window
from pyspark.sql.types import IntegerType, FloatType, StringType
from pyspark.sql.types import ArrayType

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::preprocess") \
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


def prepareSaleDF(startDate, endDate):
    assert startDate <= endDate, 'startDate:%s must <= endDate:%s' % (startDate, endDate)

    logging.info('prepareSaleDF(): startDate:%s, endDate:%s', startDate, endDate)

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
                     .withColumn('amt', ((F.col('ware_num')*F.col('ware_price')-F.col('promotion_price'))/F.lit(100.0)).astype(FloatType())) \
                     .fillna({'amt': 0.0}) \
                     .select('vender_id', 'store_id', 'sku', 'date', 'salequantity', 'amt')

    offlineStoreDF = fastjoin(offlineDF, storeDF, ['store_id', 'vender_id']).select('mandt',
                                                                                    'werks',
                                                                                    'sku',
                                                                                    'date',
                                                                                    'salequantity',
                                                                                    'amt')

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
                    .withColumn('amt', ((F.col('ware_num')*F.col('ware_price')-F.col('promotion_price'))/F.lit(100.0)).astype(FloatType())) \
                    .fillna({'amt': 0.0}) \
                    .select('vender_id', 'store_id', 'sku', 'date', 'salequantity', 'amt')

    freegoStoreDF = fastjoin(freegoDF, storeDF, ['store_id', 'vender_id']).select('mandt',
                                                                                  'werks',
                                                                                  'sku',
                                                                                  'date',
                                                                                  'salequantity',
                                                                                  'amt')

    # 线下和自由购(线上)销量合并
    saleDF = safeunion(offlineStoreDF, freegoStoreDF)

    return saleDF


def preparePromoDF(startDate, endDate):
    assert startDate <= endDate, 'startDate:%s must <= endDate:%s' % (startDate, endDate)

    logging.info('preparePromoDF(): startDate:%s, endDate:%s', startDate, endDate)

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

    promoDF = fastjoin(siteDF, itemDF, ['mandt', 'sku', 'ref_promo', 'aktnr']).select('mandt',
                                                                                      'werks',
                                                                                      'sku',
                                                                                      'ref_promo',
                                                                                      'aktnr',
                                                                                      'vkdab',
                                                                                      'vkdbi')

    return promoDF


def labelWerks():
    onedayAgo = datediff(RUNDATE, -1)
    sixMonthAgo = datediff(onedayAgo, -180)

    logging.info('labelWerks(): onedayAgo:%s, sixMonthAgo:%s', onedayAgo, sixMonthAgo)

    saleDF = prepareSaleDF(sixMonthAgo, onedayAgo)

    classDF = spark.table(WITHDB('etl_class')).select('middle_class', 'sku')

    saleDF = fastjoin(saleDF, classDF, ['sku'])

    # 展开促销周期的每一天
    def expandDays(vkdab, vkdbi):
        assert vkdab <= vkdbi, 'vkdab:%s must <= vkdbi:%s' % (vkdab, vkdbi)
        start, end = vkdab, vkdbi
        s = datetime.datetime.strptime(start, '%Y%m%d')
        e = datetime.datetime.strptime(end, '%Y%m%d')
        dateIsPromo = [datediff(start, +n) for n in range((e-s).days+1)]
        return dateIsPromo

    expandDaysFunc = F.udf(expandDays, ArrayType(StringType(), False))

    promoDF = preparePromoDF(sixMonthAgo, onedayAgo)

    promoDF = promoDF.select(F.col('mandt'),
                             F.col('werks'),
                             F.col('sku'),
                             F.explode(expandDaysFunc('vkdab', 'vkdbi')).alias('date')).distinct()
    promoDF = promoDF.withColumn('promo_label', F.lit(1))

    # 销量表是否促销标记
    saleDF = fastjoin(saleDF, promoDF, ['mandt', 'werks', 'sku', 'date'], 'left').fillna({'promo_label': 0})

    # 来客数：门店小票交易数
    # 分促销/正常情况，按照middle_class对门店按来客数排名
    winSpec = Window.partitionBy('promo_label', 'mandt', 'middle_class').orderBy(F.desc('customer_cnt'))
    rankDF = saleDF.groupBy('promo_label', 'mandt', 'werks', 'middle_class') \
                   .agg(F.count('*').alias('customer_cnt')) \
                   .withColumn('rank', F.row_number().over(winSpec))
    rankMaxDF = rankDF.groupBy('promo_label', 'mandt', 'middle_class').agg(F.max('rank').alias('rank_max'))

    def mklabel(rank, rankMax):
        MAXLABLE = 5
        chunksize = rankMax/MAXLABLE
        for i in range(MAXLABLE):
            if rank < i*chunksize:
                return i
        return MAXLABLE

    mklabelFunc = F.udf(mklabel, IntegerType())
    clusterDF = fastjoin(rankDF, rankMaxDF, ['promo_label', 'mandt', 'middle_class']).withColumn('label', mklabelFunc('rank', 'rank_max')) \
                                                                                     .withColumnRenamed('rank_max', 'len_total')

    # 促销:门店聚类结果
    promClusterDF = clusterDF.filter('promo_label=1').select('mandt',
                                                             'middle_class',
                                                             'werks',
                                                             'label',
                                                             'len_total')

    # Save hive with partition
    promClusterDF = promClusterDF.withColumn('vender_id', F.lit(VENDERID)) \
                                 .withColumn('type', F.lit('prom'))

    savehive(promClusterDF,
             ['vender_id', 'type'],
             'vender_id="{0}", type="{1}"'.format(VENDERID, 'prom'),
             WITHDB('preprocess_labelwerks'))

    # 正常:门店聚类结果
    normClusterDF = clusterDF.filter('promo_label=0').select('mandt',
                                                             'middle_class',
                                                             'werks',
                                                             'label',
                                                             'len_total')

    # Save hive with partition
    normClusterDF = normClusterDF.withColumn('vender_id', F.lit(VENDERID)) \
                                 .withColumn('type', F.lit('normal'))

    savehive(normClusterDF,
             ['vender_id', 'type'],
             'vender_id="{0}", type="{1}"'.format(VENDERID, 'normal'),
             WITHDB('preprocess_labelwerks'))


def sixMonth():
    onedayAgo = datediff(RUNDATE, -1)
    sixMonthAgo = datediff(onedayAgo, -180)

    logging.info('sixMonth(): onedayAgo:%s, sixMonthAgo:%s', onedayAgo, sixMonthAgo)

    promoDF = preparePromoDF(sixMonthAgo, onedayAgo)

    promoDF = promoDF.groupBy('mandt', 'werks', 'sku', 'ref_promo') \
                     .agg(F.collect_list(F.array('vkdab', 'vkdbi')).alias('aktnr_list'))

    promoDF = promoDF.groupBy('mandt', 'werks', 'sku') \
                     .agg(F.collect_list('aktnr_list').alias('promo_list'))

    saleDF = prepareSaleDF(sixMonthAgo, onedayAgo)

    saleDF = saleDF.groupBy('mandt', 'werks', 'sku') \
                   .agg(F.collect_list(F.array('date', 'salequantity')).alias('date_salequantity_list'))

    salepromoDF = fastjoin(saleDF, promoDF, ['mandt', 'werks', 'sku'], 'left')

    def avgMedian(promo_list, date_salequantity_list):
        if promo_list is None:  # 该商品没有任何促销
            promo_list = []
        dateIsPromo = []  # 所有是促销的日期
        for aktnr_list in promo_list:  # [[(s,e), (s,e)], [(s,e), (s,e)]]
            for aktnr in aktnr_list:
                assert len(aktnr) == 2, 'want:tuple(vkdab, vkdbi), have:%s' % aktnr
                begin, end = aktnr[0], aktnr[1]
                while begin <= end:
                    dateIsPromo.append(begin)
                    begin = datediff(begin, +1)
        dateIsPromo = list(set(dateIsPromo))
        dateIsPromo.sort()

        # 从第一次有销量的时间开始，认为商品一直处于上架状态
        date_salequantity_list.sort()
        firstDate = date_salequantity_list[0][0]
        dayCount = daycount(firstDate, onedayAgo)
        normQtys, promQtys = [], []
        for date_salequantity in date_salequantity_list:
            date, salequantity = date_salequantity[0], date_salequantity[1]
            if date in dateIsPromo:  # 促销
                promQtys.append(float(salequantity))
            else:                    # 正常
                normQtys.append(float(salequantity))
        # 中位数
        medianNorm, medianProm = 1.0, 1.0
        if len(normQtys) > 0:
            medianNorm = float(np.median(np.array(normQtys)))
        if len(promQtys) > 0:
            medianProm = float(np.median(np.array(promQtys)))
        # 中位数(没有销量的日期用0.0补齐)
        avgNorm, avgProm = 0.0, 0.0
        if len(normQtys) > 0:
            avgNorm = float(np.mean(np.array(normQtys+[0.0]*(dayCount-len(dateIsPromo)-len(normQtys)))))
        if len(promQtys) > 0:
            avgProm = float(np.mean(np.array(promQtys+[0.0]*(len(dateIsPromo)-len(promQtys)))))
        return [avgNorm, avgProm, medianNorm, medianProm]

    avgMedianFunc = F.udf(avgMedian, ArrayType(FloatType(), False))

    salepromoDF = salepromoDF.withColumn('qty_amt', avgMedianFunc('promo_list', 'date_salequantity_list')) \
                             .withColumn('avg_qty_norm', F.col('qty_amt').getItem(0)) \
                             .withColumn('avg_qty_prom', F.col('qty_amt').getItem(1)) \
                             .withColumn('median_qty_norm', F.col('qty_amt').getItem(2)) \
                             .withColumn('median_qty_prom', F.col('qty_amt').getItem(3))

    # 正常销量中位数/及补0后销量中位数
    normDF = salepromoDF.select(F.col('mandt'),
                                F.col('werks'),
                                F.col('sku'),
                                F.col('avg_qty_norm').alias('avg_qty'),
                                F.col('median_qty_norm').alias('qty_median'))

    # Save hive with partition
    normDF = normDF.withColumn('vender_id', F.lit(VENDERID)) \
                   .withColumn('type', F.lit('normal')) \
                   .withColumn('dt', F.lit(RUNDATE))

    savehive(normDF,
             ['vender_id', 'type', 'dt'],
             'vender_id="{0}", type="{1}", dt="{2}"'.format(VENDERID, 'normal', RUNDATE),
             WITHDB('preprocess_sixmonth'))

    # 促销销量中位数/及补0后的销量中位数
    promDF = salepromoDF.select(F.col('mandt'),
                                F.col('werks'),
                                F.col('sku'),
                                F.col('avg_qty_prom').alias('avg_qty'),
                                F.col('median_qty_prom').alias('qty_median'))

    # Save hive with partition
    promDF = promDF.withColumn('vender_id', F.lit(VENDERID)) \
                   .withColumn('type', F.lit('prom')) \
                   .withColumn('dt', F.lit(RUNDATE))

    savehive(promDF,
             ['vender_id', 'type', 'dt'],
             'vender_id="{0}", type="{1}", dt="{2}"'.format(VENDERID, 'prom', RUNDATE),
             WITHDB('preprocess_sixmonth'))


def oneWeek():
    onedayAgo = datediff(RUNDATE, -1)
    weekAgo = datediff(onedayAgo, -6)

    logging.info('oneWeek(): onedayAgo:%s, weekAgo:%s', onedayAgo, weekAgo)

    promoDF = preparePromoDF(weekAgo, onedayAgo)

    promoDF = promoDF.groupBy('mandt', 'ref_promo', 'werks', 'sku') \
                     .agg(F.collect_list(F.array('vkdab', 'vkdbi')).alias('aktnr_list'))

    promoDF = promoDF.groupBy('mandt', 'werks', 'sku') \
                     .agg(F.collect_list('aktnr_list').alias('promo_list'))

    # 门店商品聚类信息
    classDF = spark.table(WITHDB('etl_class')).select('middle_class', 'sku')

    clusterDF = spark.table(WITHDB('preprocess_labelwerks')) \
                     .filter('vender_id = '+VENDERID) \
                     .select('mandt', 'type', 'middle_class', 'werks', 'label')

    werksDF = fastjoin(clusterDF, classDF, ['middle_class'])

    # TODO: Change BOOTSTRAP=False when appropriate
    # NOTE: 算法设计上要求使用最近一周清洗后的订单数据，但是在程序刚部署的一段
    # 时间内，清洗的数据表数据量还没有积累到足够的数据，需要切换到原始订单数据
    # 源实现自举。
    BOOTSTRAP = True

    if BOOTSTRAP:
        logging.info('oneWeek(): Bootstrap mode on, consider turn off it when appropriate.')
        saleDF = prepareSaleDF(weekAgo, onedayAgo)
    else:
        # 使用清洗后订单销量表
        saleDF = spark.table(WITHDB('clean_order')) \
                      .filter('dt >= '+weekAgo) \
                      .filter('dt <= '+onedayAgo) \
                      .select('mandt', 'werks', 'sku', 'date', 'salequantity', F.col('saleamt').alias('amt')) \
                      .fillna({'amt': 0.0})

    saleDF = fastjoin(saleDF, werksDF, ['mandt', 'werks', 'sku']).select('mandt',
                                                                         'werks',
                                                                         'sku',
                                                                         'label',
                                                                         'type',
                                                                         'date',
                                                                         'salequantity',
                                                                         'amt')

    saleDF = saleDF.groupBy('mandt', 'werks', 'sku', 'label', 'type') \
                   .agg(F.collect_list(F.array('date', 'salequantity')).alias('date_salequantity_list'),
                        F.collect_list(F.array('date', 'amt')).alias('date_amt_list'))

    saleDF = fastjoin(saleDF, promoDF, ['mandt', 'werks', 'sku'], 'left')

    def qtyAmt(typ, promo_list, date_salequantity_list, date_amt_list):
        if promo_list is None:  # 该商品没有任何促销
            promo_list = []
        dateIsPromo = []  # 所有是促销的日期
        for aktnr_list in promo_list:
            for aktnr in aktnr_list:
                assert len(aktnr) == 2, 'want:tuple(vkdab, vkdbi), have:%s' % aktnr
                begin, end = aktnr[0], aktnr[1]
                while begin <= end:
                    dateIsPromo.append(begin)
                    begin = datediff(begin, +1)
        dateIsPromo = list(set(dateIsPromo))
        dateIsPromo.sort()
        # 销量
        normQtys, promQtys = [], []
        date_salequantity_list.sort()
        for date_salequantity in date_salequantity_list:
            date, salequantity = date_salequantity[0], date_salequantity[1]
            if date in dateIsPromo:
                promQtys.append(float(salequantity))
            else:
                normQtys.append(float(salequantity))
        # 销售金额
        normAmts, promAmts = [], []
        date_amt_list.sort()
        for date_amt in date_amt_list:
            date, amt = date_amt[0], date_amt[1]
            if date in dateIsPromo:
                promAmts.append(float(amt))
            else:
                normAmts.append(float(amt))
        # 销量/销售金额
        if typ == 'prom':
            return [promQtys, promAmts]
        else:
            return [normQtys, normAmts]

    qtyAmtFunc = F.udf(qtyAmt, ArrayType(ArrayType(FloatType(), False), False))

    saleDF = saleDF.select(F.col('mandt'),
                           F.col('werks'),
                           F.col('sku'),
                           F.col('label'),
                           F.col('type'),
                           qtyAmtFunc('type', 'promo_list', 'date_salequantity_list', 'date_amt_list').alias('qty_amt'))

    qtyamtDF = saleDF.groupBy('mandt', 'sku', 'label', 'type') \
                     .agg(F.collect_list('qty_amt').alias('qty_amt_list'))

    def median(qty_amt_list):
        Qtys, Amts = [], []
        for qty_amt in qty_amt_list:
            qtys, amts = qty_amt[0], qty_amt[1]
            for qty in qtys:
                Qtys.append(qty)
            for amt in amts:
                Amts.append(amt)

        if len(Qtys) > 0:
            orderCnt = float(len(Qtys))
            medianQty = float(np.median(np.array(Qtys)))
            maxQty = float(np.amax(np.array(Qtys)))
        else:
            orderCnt, medianQty, maxQty = 0.0, 1.0, 1.0

        if len(Amts) > 0:
            medianAmt = float(np.median(np.array(Amts)))
        else:
            medianAmt = 0.0
        return [medianQty, medianAmt, maxQty, orderCnt]

    medianFunc = F.udf(median, ArrayType(FloatType(), False))

    qtyamtDF = qtyamtDF.select(F.col('mandt'), F.col('sku'), F.col('label'), F.col('type'), medianFunc('qty_amt_list').alias('qty_amt_info')) \
                       .withColumn('qty_median', F.col('qty_amt_info').getItem(0)) \
                       .withColumn('amt_median', F.col('qty_amt_info').getItem(1)) \
                       .withColumn('qty_max', F.col('qty_amt_info').getItem(2)) \
                       .withColumn('order_cnt', F.col('qty_amt_info').getItem(3)) \
                       .select('mandt', 'sku', 'label', 'qty_median', 'amt_median', 'qty_max', 'order_cnt', 'type').cache()

    # 正常：最近一周销量中位数，销量最大值，金额中位数
    normDF = qtyamtDF.filter('type="normal"') \
                     .drop('type') \
                     .select('mandt', 'sku', 'label', 'qty_median', 'amt_median', 'qty_max', 'order_cnt')

    # Save hive with partition
    normDF = normDF.withColumn('vender_id', F.lit(VENDERID)) \
                   .withColumn('type', F.lit('normal')) \
                   .withColumn('dt', F.lit(RUNDATE))

    savehive(normDF,
             ['vender_id', 'type', 'dt'],
             'vender_id="{0}", type="{1}", dt="{2}"'.format(VENDERID, 'normal', RUNDATE),
             WITHDB('preprocess_oneweek'))

    # 促销：最近一周销量中位数，销量最大值，金额中位数
    promDF = qtyamtDF.filter('type="prom"') \
                     .drop('type') \
                     .select('mandt', 'sku', 'label', 'qty_median', 'amt_median', 'qty_max', 'order_cnt')

    # Save hive with partition
    promDF = promDF.withColumn('vender_id', F.lit(VENDERID)) \
                   .withColumn('type', F.lit('prom')) \
                   .withColumn('dt', F.lit(RUNDATE))

    savehive(promDF,
             ['vender_id', 'type', 'dt'],
             'vender_id="{0}", type="{1}", dt="{2}"'.format(VENDERID, 'prom', RUNDATE),
             WITHDB('preprocess_oneweek'))


if __name__ == '__main__':
    logging.info('start preprocess')

    RUNDATE = datenow()

    labelWerks()
    sixMonth()
    oneWeek()
    logging.info('finish preprocess')
    spark.stop()
