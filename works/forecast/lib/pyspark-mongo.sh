#!/usr/bin/bash

# Test pyspark export data to mongodb

pyspark --conf "spark.mongodb.input.uri=mongodb://reportcenter:0jtp3Gdn@10.13.3.26:27017/reportcenter?readPreference=primaryPreferred" \
        --conf "spark.mongodb.output.uri=mongodb://reportcenter:0jtp3Gdn@10.13.3.26:27017/reportcenter" \
        --packages org.mongodb.spark:mongo-spark-connector_2.11:2.2.2
