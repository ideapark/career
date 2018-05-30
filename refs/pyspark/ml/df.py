"""
https://github.com/apache/spark/blob/master/examples/src/main/python/ml/dataframe_example.py
"""

from __future__ import print_function

import os
import tempfile
import shutil

from pyspark.sql import SparkSession
from pyspark.mllib.stat import Statistics
from pyspark.mllib.util import MLUtils

spark = SparkSession.builder.appName("DataFrameML").getOrCreate()

df = spark.read.format("libsvm").load("testdata/libsvm.data").cache()
print("Schema from LIBSVM:")
df.printSchema()
print("Loaded training data as a DataFrame with " + str(df.count()) + " records.")

# show statistical summary of labels
labelSummary = df.describe("label")
labelSummary.show()

# convert features column to an RDD of vectors
features = MLUtils.convertVectorColumnsFromML(df, "features") \
                  .select("features") \
                  .rdd \
                  .map(lambda r: r.features)
summary = Statistics.colStats(features)
print("Selected features solumn with average values:\n" + str(summary.mean()))

# save the records in a parquet file
tempdir = tempfile.NamedTemporaryFile(delete=False).name
os.unlink(tempdir)
print("Saving to " + tempdir + " as Parquet file.")
df.write.parquet(tempdir)

# load the records back
print("Loading Parquet file with UDT from " + tempdir)
newDF = spark.read.parquet(tempdir)
print("Schema from Parquet:")
newDF.printSchema()
shutil.rmtree(tempdir)

spark.stop()
