# 销量预测

### 流程说明
- ETL: 数据抽取，用于将增量更新的促销档期数据汇总到全量表，用于销量预测其他阶段使用。
- PREPROCESS: 计算最近半年的销量中位数，最近一周的销量中位数、订单数和销售金额，用于数据清理。
- CLEAN: 按照数据清理规则对销量数据（线上/线下）进行清洗剔除。
- DMS: 在清洗后的销量数据上（线上+线下）按照预测逻辑预测明日销量。
- DATAIO: 从rest https导入供商配置数据/导出Hive数据到Mongo。

### 数据逻辑依赖图

```
                                                                          Web UI config data
                                                                                  ↓
                                                                               +-----+                                    +--------+
                                                                        +----> | DMS | -------> Sale Forecast Table ----> | DATAIO | ----> Mongo table ----> Web UI
  Delta Promotion Table                                                 |      +-----+                                    +--------+
       |                                                                |
    +-----+                                                      Cleaned Sale Table <-----+
    | ETL |                                                                               |
    +-----+                                                                               |
       |                             +------------+    Latest Week Median/Amount      +-------+
       +----> Sigma Promotion -----> | PREPROCESS | -----> Six Month Median --------> | CLEAN | <------ Sale Table (online+offline+[global?+o2o?])
                  Table              +------------+                                   +-------+
                                           ↑                                             ↑
                                     Web UI config data                            Web UI config data
```

### 部署流程图

```
                 +-----+
                 | ETL |<----------------+
                 +-----+                 |
                    ↓                    |
                +-------+                |
                | CLEAN |                |
                +-------+                |
                    ↓                    |
                 +-----+                 |
  RUNDATE=dayN   | DMS |                 |  RUNDATE = dayN+1
                 +-----+                 |
                    ↓                    |
                +--------+               |
                | DATAIO |               |
                +--------+               |
                    ↓                    |
              +------------+             |
              | PREPROCESS |             |
              +------------+             |
                    |                    |
                    +--------------------+
```

### 数据时序关系（重要）
- PREPROCESS: dayN 的预处理结果 CLEAN dayN+1 使用
- DATAIO: dayN 导入的供商配置 CLEAN & DMS dayN+1 才会生效
