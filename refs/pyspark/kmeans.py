"""
ref: https://github.com/apache/spark/blob/master/examples/src/main/python/kmeans.py
"""

from __future__ import print_function

import sys

import numpy as np
from pyspark.sql import SparkSession

def parseVector(line):
    return np.array([float(x) for x in line.split(' ')])

def closestPoint(p, centers):
    bestIndex = 0
    closest = float("+inf")
    for i in range(len(centers)):
        tempDist = np.sum((p-centers[i]) ** 2)
        if tempDist < closest:
            closest = tempDist
            bestIndex = i
    return bestIndex

print("""WARN: This is a naive implementation of KMeans Clustering and is given
as an example! Please refer to examples/src/main/python/ml/kmeans_example.py for an
example on how to use ML's KMeans implementation.""", file=sys.stderr)

spark = SparkSession.builder.appName("PythonKMeans").getOrCreate()

lines = spark.read.text('testdata/kmeans.data').rdd.map(lambda r: r[0])
data = lines.map(parseVector).cache()
K = 20
convergeDist = float(2.0)

kPoints = data.takeSample(False, K, 1)
tempDist = 1.0

while tempDist > convergeDist:
    closest = data.map(lambda p: (closestPoint(p,kPoints), (p,1)))
    pointStats = closest.reduceByKey(lambda p1_c1, p2_c2: (p1_c1[0]+p2_c2[0], p1_c1[1]+p2_c2[1]))
    newPoints = pointStats.map(lambda st: (st[0], st[1][0]/st[1][1])).collect()
    tempDist = sum(np.sum((kPoints[iK]-p)**2) for (iK,p) in newPoints)
    for (iK,p) in newPoints:
        kPoints[iK] = p

print("Final centers: " + str(kPoints))

spark.stop()
