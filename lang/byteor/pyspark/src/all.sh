#!/usr/bin/env bash

# AUTHOR: Zhou Peng <p@ctriple.cn>

# Run all spark tasks sequentially:
#
# 1) ETL
# 2) CLEAN
# 3) DMS
# 4) DATAIO
# 5) PREPROCESS

set -x

function spark-run
{
    echo "$(date '+%Y-%m-%d %H:%M:%S') spark-run(): start $1"

    spark-submit \
        --master yarn-cluster \
        --num-executors 40 \
        --executor-cores 2 \
        --executor-memory 3000M \
        --driver-memory 2g \
        --packages org.mongodb.spark:mongo-spark-connector_2.11:2.2.0 \
        --conf spark.yarn.executor.memoryOverhead=2000 \
        --conf spark.kryoserializer.buffer.max=2000m \
        --conf spark.kryoserializer.buffer=40m \
        --conf spark.port.maxRetries=100 \
        --queue ddw_wumart \
        $*

    echo "$(date '+%Y-%m-%d %H:%M:%S') spark-run(): finish $1"
}


# Run cycle defined as follows:
#
#  +----<----------<-----------<------+
#  ↓                                  ↑
# ETL -> CLEAN -> DMS -> DATAIO -> PREPROCESS
#

# ETL
spark-run etl.py

# CLEAN
spark-run clean.py

# DMS
spark-run dms.py

# DATAIO
spark-run dataio.py

# PREPROCESS
spark-run preprocess.py
