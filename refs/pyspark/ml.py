#+TITLE: Apache Spark Tuturial Machine Learning
#+URL: https://www.datacamp.com/community/tutorials/apache-spark-tutorial-machine-learning
#+EMAIL: p@ctriple.cn

from pyspark.sql import SparkSession
from pyspark.sql import Row
from pyspark.sql.types import *
from pyspark.sql.functions import *
from pyspark.ml.linalg import DenseVector
from pyspark.ml.feature import StandardScaler
from pyspark.ml.regression import LinearRegression

spark = SparkSession.builder \
                    .master("local") \
                    .appName("Linear Regression Model") \
                    .config("spark.executor.memory", "1gb") \
                    .getOrCreate()

sc = spark.sparkContext

# http://www.dcc.fc.up.pt/~ltorgo/Regression/cal_housing.tgz
rdd = sc.textFile('/home/esc/CaliforniaHousing/cal_housing.data')
header = sc.textFile('/home/esc/CaliforniaHousing/cal_housing.domain')

#### Data Exploration
print header.collect()

rdd = rdd.map(lambda line: line.split(","))

print rdd.take(2)
print rdd.first()
print rdd.top(2)

# map the rdd (Represents Data) to a df (DataFrames)
df = rdd.map(lambda line: Row(longitude=line[0],
                              latitude=line[1],
                              housingMedianAge=line[2],
                              totalRooms=line[3],
                              totalBedRooms=line[4],
                              population=line[5],
                              households=line[6],
                              medianIncome=line[7],
                              mediaHouseValue=line[8])).toDF()

df.show()
df.printSchema()

df = df.withColumn("longitude", df["longitude"].cast(FloatType())) \
       .withColumn("latitude", df["latitude"].cast(FloatType())) \
       .withColumn("housingMedianAge", df["housingMedianAge"].cast(FloatType())) \
       .withColumn("totalRooms", df["totalRooms"].cast(FloatType())) \
       .withColumn("totalBedRooms", df["totalBedRooms"].cast(FloatType())) \
       .withColumn("population", df["population"].cast(FloatType())) \
       .withColumn("households", df["households"].cast(FloatType())) \
       .withColumn("medianIncome", df["medianIncome"].cast(FloatType())) \
       .withColumn("mediaHouseValue", df["mediaHouseValue"].cast(FloatType()))

df.show()
df.printSchema()
df.groupBy("housingMedianAge").count().sort("housingMedianAge", ascending=False).show()
df.describe().show()

#### Preprocessing The Targe Values
df = df.withColumn("mediaHouseValue", col("mediaHouseValue")/100000)

print df.take(2)

#### Feature Engineering
roomsPerHousehold = df.select(col("totalRooms")/col("households"))
populationPerHousehold = df.select(col("population")/col("households"))
bedroomPerRoom = df.select(col("totalBedRooms")/col("totalRooms"))

df = df.withColumn("roomsPerHousehold", col("totalRooms")/col("households")) \
       .withColumn("populationPerHousehold", col("population")/col("households")) \
       .withColumn("bedroomPerRoom", col("totalBedRooms")/col("totalRooms"))

print df.first()

df = df.select("mediaHouseValue",
               "totalBedRooms",
               "population",
               "medianIncome",
               "roomsPerHousehold",
               "populationPerHousehold",
               "bedroomPerRoom")

#### Standardization
input_data = df.rdd.map(lambda x: (x[0], DenseVector(x[1:])))

df = spark.createDataFrame(input_data, ["label", "features"])

standardScaler = StandardScaler(inputCol="features", outputCol="features_scaled")
scaler = standardScaler.fit(df)
scaled_df = scaler.transform(df)
print scaled_df.take(2)

#### Building A Machine Learning Model With Spark ML
train_data, test_data = scaled_df.randomSplit([.8,.2], seed=1234)
lr = LinearRegression(labelCol="label", maxIter=10, regParam=0.3, elasticNetParam=0.8)
linearModel = lr.fit(train_data)
predicted = linearModel.transform(test_data)
predictions = predicted.select("prediction").rdd.map(lambda x: x[0])
labels = predicted.select("label").rdd.map(lambda x: x[0])
predictionAndLabel = predictions.zip(labels).collect()
print predictionAndLabel[:5]

#### Evaluating the Model
print linearModel.coefficients
print linearModel.intercept
print linearModel.summary.rootMeanSquaredError
print linearModel.summary.r2

# Stop spark session
spark.stop()
