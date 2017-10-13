from pyspark.sql import SparkSession

# Entry point into all functionality in Spark
spark = SparkSession.builder \
                    .appName("Python Spark SQL basic example") \
                    .config("spark.executor.memory", "2gb") \
                    .getOrCreate()

# Creating DataFrames
df = spark.read.json('testdata/employees.json')
df.show()

# Print the schema in a tree format
df.printSchema()

# Select only the "name" column
df.select("name").show()

# Select everybody, but increment the salary by 1000
df.select(df['name'], df['salary'] + 1000).show()

# Select people earn more than $3000
df.filter(df['salary'] > 3000).show()

# Register the DataFrames as a SQL temporary view
df.createOrReplaceTempView("employees")
sqlDF = spark.sql("SELECT * FROM employees")
sqlDF.show()

# Register the DataFrames as a global temporary view
df.createGlobalTempView("employees")
# Global temporary view is tied to a system preserved database `global_temp`
spark.sql("SELECT * FROM global_temp.employees").show()
# Global temporary view is cross-session
spark.newSession().sql("SELECT * FROM global_temp.employees").show()

spark.stop()
