#!/usr/bin/env python
# -*- coding: utf-8 -*-
# AUTHOR: Zhou Peng <p@ctriple.cn>

# 数据迁移(MIGRATE) -- (USED ONLY ONETIME)
#
# 替换线上老版本步骤：
# 1. Copy所有线上中间表和结果表(基础数据表除外)，表名选择当前新版本程序使用的表名。
# 2. 处理新旧表字段变化逻辑
# 3. 新旧版本同时在线运行几天后对比数据
# 4. 停用旧版本，新版本开始生效

import logging
import pyspark.sql.functions as F
from pyspark.sql import SparkSession

logging.basicConfig(format='%(asctime)s %(levelname)-8s [%(filename)s:%(lineno)-3d] %(message)s',
                    level=logging.INFO,
                    datefmt='%Y-%m-%d %H:%M:%S')

spark = SparkSession.builder \
                    .appName("supplychain::forecast::migrate") \
                    .config("spark.sql.tungsten.enabled", "false") \
                    .config("spark.sql.crossJoin.enabled", "true") \
                    .config("spark.serializer", "org.apache.spark.serializer.KryoSerializer") \
                    .config("spark.default.parallelism", 60) \
                    .config("hive.exec.dynamic.partition", "true") \
                    .config("hive.exec.dynamic.partition.mode", "nonstrict") \
                    .config("hive.exec.max.dynamic.partitions", "10000") \
                    .enableHiveSupport() \
                    .getOrCreate()


VENDERDB = 'ddw_wumart'


def WITHDB(tableName):
    SEP = '.'
    dbtable = VENDERDB + SEP + tableName
    logging.info('WITHDB(): %s', dbtable)
    return dbtable


if __name__ == '__main__':
    MIGRATE_TABLES = [
        #        OLD TABLE                  NEW TABLE                     PARTITION COLUMNS (NOTE: order does matter!!!)

        # ETL
        ('m_zpromotionplanitem',     'etl_promoplanitem_sigma',              []),
        ('m_zpromotionplanitemsite', 'etl_promoplanitemsite_sigma',          []),

        # PREPROCESS
        ('dms_mc_werks_cluster',     'preprocess_labelwerks',                ['vender_id', 'type']),
        ('dms_data_clean_year',      'preprocess_sixmonth',                  ['vender_id', 'type', 'dt']),
        ('dms_data_clean_recent',    'preprocess_oneweek',                   ['vender_id', 'type', 'dt']),

        # CLEAN
        ('dms_data_clean_partition', 'clean_order',                          ['vender_id', 'dt']),

        # DMS
        ('dms_data',                 'forecast_dms_data',                    ['vender_id', 'dt']),
    ]

    for mtable in MIGRATE_TABLES:
        oldtable, newtable, pcols = mtable[0], mtable[1], mtable[2]

        logging.info('MIGRATE: oldtable:%s -> newtable:%s', oldtable, newtable)

        # NOTE: Be carefull
        I_Know_What_I_Am_Doing = False
        assert I_Know_What_I_Am_Doing, 'Be Careful Dangerous Operations!!!'
        spark.sql('DROP TABLE IF EXISTS {0}'.format(WITHDB(newtable)))

        dataDF = spark.table(WITHDB(oldtable))

        logging.info('migrate: %s', dataDF.dtypes)

        # NOTE: 特殊处理表的不兼容变更
        if oldtable == 'dms_data_clean_partition':
            dataDF = dataDF.withColumn('clean_flag', F.when(F.col('flag').isin('0_5_p', '0_5_n'), F.lit('ALL_PASSED')).otherwise(F.lit('clean_3'))) \
                           .drop('raw_flag') \
                           .drop('flag')

        # Save hive with partition when needed
        if len(pcols) > 0:
            dataDF.write \
                  .mode('overwrite') \
                  .partitionBy(pcols) \
                  .saveAsTable(WITHDB(newtable))
        else:
            dataDF.write \
                  .mode('overwrite') \
                  .saveAsTable(WITHDB(newtable))
