#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 数据抽取(ETL)
#
# 促销数据是按每天增量更新且只保留最近几个月数据,etl程序抽取每天数据汇总到全量
# 表,作为销量预测计算基础表。

import logging
import pyspark.sql.functions as F
from pyspark.sql import SparkSession
from pyspark.sql.types import IntegerType

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::etl") \
                    .config("spark.sql.tungsten.enabled", "false") \
                    .config("spark.sql.crossJoin.enabled", "true") \
                    .config("spark.serializer", "org.apache.spark.serializer.KryoSerializer") \
                    .config("spark.default.parallelism", 60) \
                    .config("hive.exec.dynamic.partition", "true") \
                    .config("hive.exec.dynamic.partition.mode", "nonstrict") \
                    .config("hive.exec.max.dynamic.partitions", "10000") \
                    .enableHiveSupport() \
                    .getOrCreate()

VENDERDB = 'wumart2dmall'


def WITHDB(tableName):
    SEP = '.'
    dbtable = VENDERDB + SEP + tableName
    logging.info('WITHDB(): %s', dbtable)
    return dbtable


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


def etl_promo():
    # 将按天增量更新的门店商品促销信息抽取到促销全量表：
    #
    # NOTE: 增量数据有可能是对部分全量数据的更新;因此不能直接将增量数据Union到
    #       全量数据
    #
    # 计算公式: (SigmaTable - (SigmaTable ⋂ DeltaTable)) ⋃ DeltaTable

    tablePairs = [
        # 商品促销
        ('ods_zpromotionplanitem_day',                         # 增量表
         'etl_promoplanitem_sigma',                            # 全量表
         'tmp_etl_promoplanitem_sigma',                        # 临时中转全量表
         ['mandt', 'matnr', 'ref_promo', 'aktnr', 'pstop']),   # 表字段

        # 门店促销
        ('ods_zpromotionplanitemsite_day',                                      # 增量表
         'etl_promoplanitemsite_sigma',                                         # 全量表
         'tmp_etl_promoplanitemsite_sigma',                                     # 临时中转全量表
         ['mandt', 'werks', 'matnr', 'ref_promo', 'aktnr', 'vkdab', 'vkdbi']),  # 表字段
    ]

    for tablePair in tablePairs:
        deltaTable, sigmaTable, tmpSigmaTable, tableCols = tablePair[0], tablePair[1], tablePair[2], tablePair[3]

        # 增量表最近一天的分区时间
        dtDataList = spark.table(WITHDB(deltaTable)) \
                          .orderBy('dt', ascending=False) \
                          .take(1)
        assert len(dtDataList) == 1, 'Why table:%s empty?' % WITHDB(deltaTable)

        dtData = dtDataList[0]
        maxdt = dtData['dt']

        logging.info('etl_promo(): table:%s max dt:%s', WITHDB(deltaTable), maxdt)

        flagDF = spark.table(WITHDB(deltaTable)) \
                      .filter('dt='+maxdt) \
                      .select(F.col('mandt'), F.col('ref_promo')) \
                      .dropDuplicates(['mandt', 'ref_promo']) \
                      .withColumn('_tmp_flag', F.lit(1))

        sigmaDF = spark.table(WITHDB(sigmaTable)).select(tableCols)

        # alphaDF = (SigmaTable - (SigmaTable ⋂ DeltaTable))
        alphaDF = fastjoin(sigmaDF, flagDF, ['mandt', 'ref_promo'], 'left').filter(F.col('_tmp_flag').isNull()) \
                                                                           .drop('_tmp_flag')

        deltaDF = spark.table(WITHDB(deltaTable)) \
                       .filter('dt='+maxdt) \
                       .select(tableCols)

        df = safeunion(alphaDF, deltaDF)

        # NOTE: Spark限制不能直接Overwrite正在使用的表(数据一致性保证)，这里引入了中转临时表
        df.write.mode('overwrite').saveAsTable(WITHDB(tmpSigmaTable))
        tmpDF = spark.table(WITHDB(tmpSigmaTable))
        tmpDF.write.mode('overwrite').saveAsTable(WITHDB(sigmaTable))


def etl_class():
    """
    从商品主数据表抽取商品大中小分类映射关系

    以物美为例：
    U课  -> 大分类(big_class)
    MC  -> 中分类(middle_class)
    EMC -> 小分类(small_class)
    """
    logging.info('etl_class(): running')

    articleDF = spark.table(WITHDB('m_article'))

    classDF = articleDF.filter('mandt=300') \
                       .select(F.col('puunit').alias('big_class'),
                               F.col('punam').alias('big_class_name'),
                               F.col('matkl').alias('middle_class'),
                               F.col('wgbez').alias('middle_class_name'),
                               F.col('extwg').alias('small_class'),
                               F.col('ewbez').alias('small_class_name'),
                               F.col('matnr').astype(IntegerType()).alias('sku')) \
                       .filter(F.col('sku').isNotNull()) \
                       .distinct() \
                       .dropDuplicates(['sku'])

    classDF.write \
           .mode('overwrite') \
           .saveAsTable(WITHDB('etl_class'))


if __name__ == '__main__':
    logging.info('start etl')
    etl_promo()
    etl_class()
    logging.info('finish etl')
    spark.stop()
