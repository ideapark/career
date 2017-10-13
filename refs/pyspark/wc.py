"""
ref: https://github.com/apache/spark/blob/master/examples/src/main/python/wordcount.py
"""

from __future__ import print_function

import sys
from operator import add

from pyspark.sql import SparkSession

spark = SparkSession.builder.appName("PythonWordCount").getOrCreate()

lines = spark.read.text("testdata/cal_housing.data").rdd.map(lambda r: r[0])
counts = lines.flatMap(lambda x: x.split(',')).map(
    lambda x: (x, 1)).reduceByKey(add)

output = counts.collect()
for (word, count) in output:
    print("%s: %i" % (word, count))

spark.stop()
