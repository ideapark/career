#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 数据导入导出(DATAIO)
#
# 1. 从rest https导入供商DMS配置数据到Hive
# 2. 从Hive导出DMS结果数据到Mongo

# TODO(zhoupeng): switch mongo database by current vender

import json
import logging
import datetime
import pyspark.sql.functions as F
from pyspark.sql.types import IntegerType
from pyspark.sql import SparkSession

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::dataio") \
                    .config("spark.sql.tungsten.enabled", "false") \
                    .config("spark.sql.crossJoin.enabled", "true") \
                    .config("spark.serializer", "org.apache.spark.serializer.KryoSerializer") \
                    .config("spark.default.parallelism", 60) \
                    .config("hive.exec.dynamic.partition", "true") \
                    .config("hive.exec.dynamic.partition.mode", "nonstrict") \
                    .config("hive.exec.max.dynamic.partitions", "10000") \
                    .config("spark.mongodb.input.uri", "mongodb://reportcenter:0jtp3Gdn@10.13.3.25:27017/reportcenter") \
                    .config("spark.mongodb.output.uri", "mongodb://reportcenter:0jtp3Gdn@10.13.3.25:27017/reportcenter") \
                    .enableHiveSupport() \
                    .getOrCreate()

RUNDATE = '20180501'

MONGO_READY = False

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


def httpsdata(url):
    logging.info('httpdata(): rest url:%s', url)

    try:
        import urllib2 as httpclient
        logging.info('httpconf(): we are run on python2.0+')
    except ImportError:
        import urllib.request as httpclient
        logging.info('httpconf(): we are run on python3.0+')

    try:
        # 禁用ssl验证
        import ssl
        ctx = ssl.create_default_context()
        ctx.check_hostname = False
        ctx.verify_mode = ssl.CERT_NONE

        req = httpclient.Request(url)
        req.add_header('Host', 'testsaleforecast.dmall.com')
        req.add_header('Content-Type', 'application/json;charset=utf-8')
        req.add_header('Accept', 'application/json')

        restdata = httpclient.urlopen(req, timeout=120, context=ctx).read()
    except:
        restdata = '{"error": "http timeout"}'

    logging.info('httpconf(): restdata:%s', restdata)

    return restdata.decode('utf-8')


def httpimport_holiday():
    """法定节假日导入"""
    now = datetime.datetime.now()
    year, month = now.year, now.month

    # NOTE: 在每年的12月份同步下一年的法定节假日
    if month > 11:
        yearArg = str(year+1)
    else:
        yearArg = str(year)

    logging.info('httpimport_holiday(): month:%s, yearArg:%s', month, yearArg)

    REST_URL = 'https://10.13.3.19/sf/dms_system/chinaholiday?year='+yearArg

    # Json模板: lib/dms-holiday-template.json
    originJson = httpsdata(REST_URL)

    try:
        # Simple json validation
        # 1. Assert key exists
        # 2. Assert length limitation
        holidayJson = json.loads(originJson)
        assert len(holidayJson['holidayhappy']) >= 1, 'holidayhappy missing?'
        assert len(holidayJson['holidaycry']) >= 1, 'holidaycry missing?'
    except (RuntimeError, ValueError, TypeError, KeyError) as e:
        logging.warn('httpimport_holiday() [FAILED]: malformed json - data:%s\n error:%s', originJson, e)
        return

    holidayDF = spark.createDataFrame([(originJson,)], ('origin_json',))
    holidayDF = holidayDF.withColumn('year', F.lit(yearArg))

    savehive(holidayDF,
             ['year'],
             'year="{0}"'.format(yearArg),
             WITHDB('dms_holiday'))

    logging.info('httpimport_holiday() [OK]: json:\n%s', jsonpretty(originJson))


def httpimport_conf():
    """供商配置导入"""

    REST_URL = 'https://10.13.3.19/sf/dms_system/getAll?martId='+VENDERID

    # Json模板: lib/dms-conf-template.json
    originJson = httpsdata(REST_URL)

    try:
        # Simple json validation
        # 1. Assert key exists
        # 2. Assert length limitation
        confJson = json.loads(originJson)
        assert len(confJson['goodsStatus']) >= 1, 'status missing?'
        assert len(confJson['defaultParamWeight']) == 5, 'default weights missing?'
        assert len(confJson['paramWeights']) >= 1, 'customized weights missing?'
        assert confJson['defaultCleanThreshold'] > 0, 'default clean threshold missing?'
        assert len(confJson['cleanThreshold']) >= 1, 'customized clean threshold missing?'
    except (RuntimeError, ValueError, TypeError, KeyError) as e:
        logging.warn('httpimport_conf() [FAILED]: malformed json - data:%s\n error:%s', originJson, e)
        return

    confDF = spark.createDataFrame([(originJson,)], ('origin_json',))
    confDF = confDF.withColumn('dt', F.lit(RUNDATE))

    savehive(confDF,
             ['dt'],
             'dt="{0}"'.format(RUNDATE),
             WITHDB('dms_conf'))

    logging.info('httpimport_conf() [OK]: json:\n%s', jsonpretty(originJson))


def prepareDmsExportData(startDate, endDate):
    assert startDate <= endDate, 'startDate:%s must <= endDate:%s' % (startDate, endDate)

    logging.info('prepareDmsData(): startDate:%s, endDate:%s', startDate, endDate)

    # 门店名称
    siteDF = spark.table(WITHDB('m_site')).select(F.col('werks'),
                                                  F.col('name1').alias('werks_name')) \
                                          .dropDuplicates(['werks']) \
                                          .distinct()

    # 商品名称
    skuDF = spark.table(WITHDB('m_article')).select(F.col('matnr').astype(IntegerType()).alias('sku'),
                                                    F.col('maktx').alias('sku_name')) \
                                            .dropDuplicates(['sku']) \
                                            .distinct()

    dmsDF = spark.table(WITHDB('dms_data')) \
                 .filter('dt>='+startDate) \
                 .filter('dt<='+endDate) \
                 .filter('vender_id='+VENDERID)

    dmsDF = fastjoin(dmsDF, siteDF, ['werks'], 'left').fillna({'werks_name': 'Unknown'})
    dmsDF = fastjoin(dmsDF, skuDF, ['sku'], 'left').fillna({'sku_name': 'Unknown'})

    classDF = spark.table(WITHDB('etl_class')).dropDuplicates(['sku']) \
                                              .select('big_class', 'middle_class', 'small_class', 'sku')

    dmsDF = fastjoin(dmsDF, classDF, ['sku'], 'left')

    # 使用清洗后的订单数据
    saleDF = spark.table(WITHDB('clean_order')) \
                  .filter('vender_id='+VENDERID) \
                  .filter('dt>='+startDate) \
                  .filter('dt<='+endDate) \
                  .filter('clean_flag="ALL_PASSED"') \
                  .groupBy('mandt', 'werks', 'sku', 'dt') \
                  .agg(F.sum('raw_qty').alias('real_sale'))

    dmsDF = fastjoin(dmsDF, saleDF, ['mandt', 'werks', 'sku', 'dt'], 'left').fillna({'real_sale': 0.0})

    return dmsDF


# 数据分区覆盖原理
#
# ... ...
#
# dayN-1~      dayN
#
#              dayN~      dayN+1
#                         dayN+1~      dayN+2
# -------------------------------------------
# dayN-1~      dayN~      dayN+1~      dayN+2

def mongoexport_dms():
    """DMS计算结果导出"""

    today = RUNDATE
    onedayAgo = datediff(RUNDATE, -1)

    logging.info('mongoexport_dms(): onedayAgo:%s today:%s', onedayAgo, today)

    dmsDF = prepareDmsExportData(onedayAgo, today)

    savehive(dmsDF.filter('dt='+onedayAgo),
             ['dt'],
             'dt="{0}"'.format(onedayAgo),
             WITHDB('dms_data_export'))

    savehive(dmsDF.filter('dt='+today),
             ['dt'],
             'dt="{0}"'.format(today),
             WITHDB('dms_data_export'))

    if MONGO_READY:
        dmsexpDF = spark.table(WITHDB('dms_data_export')) \
                        .filter('dt>='+onedayAgo) \
                        .filter('dt<='+today)

        # NOTE: 生成Mongo主键_id，实现数据upsert，这种方式可以完美解决数据重复导入问题
        dmsexpDF = dmsexpDF.withColumn('_id', F.sha1(F.concat('mandt', 'werks', 'sku', 'dt')))

        logging.info('mongoexport_dms(): hive table:%s, mongo table:%s, onedayAgo:%s, today:%s, count:%s',
                     WITHDB('dms_data_export'),
                     'reportcenter.dms_data',
                     onedayAgo,
                     today,
                     dmsexpDF.count())

        dmsexpDF.write \
                .format("com.mongodb.spark.sql.DefaultSource") \
                .mode('append') \
                .option('database', 'reportcenter') \
                .option('collection', 'dms_data') \
                .save()

    # 统计聚合
    dmsaggDF = dmsDF.groupBy('big_class', 'middle_class', 'small_class', 'sku', 'dt') \
                    .agg(F.sum('dms').alias('dms'),
                         F.sum('real_sale').alias('real_sale'))

    savehive(dmsaggDF.filter('dt='+onedayAgo),
             ['dt'],
             'dt="{0}"'.format(onedayAgo),
             WITHDB('dms_data_agg'))

    savehive(dmsaggDF.filter('dt='+today),
             ['dt'],
             'dt="{0}"'.format(today),
             WITHDB('dms_data_agg'))

    if MONGO_READY:
        aggexpDF = spark.table(WITHDB('dms_data_agg')) \
                        .filter('dt>='+onedayAgo) \
                        .filter('dt<='+today)

        # NOTE: 生成Mongo主键_id，实现数据upsert，这种方式可以完美解决数据重复导入问题
        aggexpDF = aggexpDF.withColumn('_id', F.sha1(F.concat('sku', 'dt')))

        logging.info('mongoexport_dms(): hive table:%s, mongo table:%s, onedayAgo:%s, today:%s, count:%s',
                     WITHDB('dms_data_agg'),
                     'reportcenter.dms_data_agg',
                     onedayAgo,
                     today,
                     aggexpDF.count())

        aggexpDF.write \
                .format("com.mongodb.spark.sql.DefaultSource") \
                .mode('append') \
                .option('database', 'reportcenter') \
                .option('collection', 'dms_data_agg') \
                .save()


def mongoexport_clean():
    """数据清洗统计导出"""

    onedayAgo = datediff(RUNDATE, -1)

    logging.info('mongoexport_clean(): onedayAgo:%s', onedayAgo)

    if not MONGO_READY:
        return

    statsDF = spark.table(WITHDB('clean_stats')) \
                   .filter('dt='+onedayAgo) \
                   .filter('vender_id='+VENDERID)

    # NOTE: 生成Mongo主键_id，实现数据upsert，这种方式可以完美解决数据重复导入问题
    statsDF = statsDF.withColumn('_id', F.sha1(F.concat('big_class', 'middle_class', 'small_class', 'vender_id', 'dt')))

    logging.info('mongoexport_clean(): hive table:%s, mongo table:%s, onedayAgo:%s, count:%s',
                 WITHDB('clean_stats'),
                 'reportcenter.clean_stats',
                 onedayAgo,
                 statsDF.count())

    statsDF.write \
           .format("com.mongodb.spark.sql.DefaultSource") \
           .mode('append') \
           .option('database', 'reportcenter') \
           .option('collection', 'clean_stats') \
           .save()


if __name__ == '__main__':
    logging.info('start dataio')

    RUNDATE = datenow()

    httpimport_holiday()
    httpimport_conf()
    mongoexport_dms()
    mongoexport_clean()
    logging.info('finish dataio')
    spark.stop()
