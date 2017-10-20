"""
https://github.com/apache/spark/blob/master/examples/src/main/python/ml/kmeans_example.py
"""

from __future__ import print_function
from pyspark.ml.clustering import KMeans
from pyspark.sql import SparkSession

spark = SparkSession.builder.appName("KMeansML").getOrCreate()

# load data
dataset = spark.read.format("libsvm").load("testdata/ml_kmeans.data")

# trains a k-means model.
kmeans = KMeans().setK(2).setSeed(1)
model = kmeans.fit(dataset)

# evaluate clustering by computing within set sum of squared errors.
wssse = model.computeCost(dataset)

print("Within Set Sum of Squared Errors = " + str(wssse))

# shows the result
centers = model.clusterCenters()
print("Cluster Centers: ")
for center in centers:
    print(center)

spark.stop()
