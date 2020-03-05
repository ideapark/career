# Etcd vs ZooKeeper vs Consul

|                                       | etcd-tip-go1.8.3 | zookeeper-r3.5.3-beta-java8 | consul-v0.8.4-go1.8.3 |
|---------------------------------------|------------------|-----------------------------|-----------------------|
| TOTAL-SECONDS                         | 27.9779 sec      | 143.8585 sec                | 135.7728 sec          |
| TOTAL-REQUEST-NUMBER                  | 1,000,000        | 1,000,000                   | 1,000,000             |
| MAX-THROUGHPUT                        | 38,526 req/sec   | 25,103 req/sec              | 15,424 req/sec        |
| AVG-THROUGHPUT                        | 35,740 req/sec   | 6,913 req/sec               | 7,365 req/sec         |
| MIN-THROUGHPUT                        | 13,418 req/sec   | 0 req/sec                   | 195 req/sec           |
| FASTEST-LATENCY                       | 5.1907 ms        | 6.7527 ms                   | 17.7190 ms            |
| AVG-LATENCY                           | 27.9170 ms       | 55.4371 ms                  | 67.8635 ms            |
| SLOWEST-LATENCY                       | 129.6517 ms      | 4427.4805 ms                | 2665.0249 ms          |
| LATENCY p10                           | 12.783090 ms     | 15.327740 ms                | 29.877078 ms          |
| LATENCY p25                           | 16.081346 ms     | 21.706332 ms                | 33.992948 ms          |
| LATENCY p50                           | 22.047040 ms     | 37.275107 ms                | 50.148835 ms          |
| LATENCY p75                           | 35.297635 ms     | 57.453429 ms                | 54.282575 ms          |
| LATENCY p90                           | 53.916881 ms     | 79.224931 ms                | 109.468689 ms         |
| LATENCY p95                           | 60.144462 ms     | 93.233345 ms                | 235.236038 ms         |
| LATENCY p99                           | 73.229996 ms     | 456.307896 ms               | 464.681161 ms         |
| LATENCY p99.9                         | 94.903421 ms     | 2128.132040 ms              | 801.018344 ms         |
| SERVER-TOTAL-NETWORK-RX-DATA-SUM      | 5.0 GB           | 5.8 GB                      | 5.6 GB                |
| SERVER-TOTAL-NETWORK-TX-DATA-SUM      | 3.8 GB           | 4.7 GB                      | 4.4 GB                |
| CLIENT-TOTAL-NETWORK-RX-SUM           | 277 MB           | 384 MB                      | 207 MB                |
| CLIENT-TOTAL-NETWORK-TX-SUM           | 1.4 GB           | 1.4 GB                      | 1.5 GB                |
| SERVER-MAX-CPU-USAGE                  | 406.67%          | 492.00%                     | 405.40%               |
| SERVER-MAX-MEMORY-USAGE               | 1.2 GB           | 17 GB                       | 4.9 GB                |
| CLIENT-MAX-CPU-USAGE                  | 468.00%          | 208.00%                     | 189.00%               |
| CLIENT-MAX-MEMORY-USAGE               | 112 MB           | 4.2 GB                      | 87 MB                 |
| CLIENT-ERROR-COUNT                    | 0                | 5,451                       | 0                     |
| SERVER-AVG-READS-COMPLETED-DELTA-SUM  | 78               | 247                         | 12                    |
| SERVER-AVG-SECTORS-READS-DELTA-SUM    | 0                | 0                           | 0                     |
| SERVER-AVG-WRITES-COMPLETED-DELTA-SUM | 97,145           | 335,8635                    | 71,342,952            |
| SERVER-AVG-SECTORS-WRITTEN-DELTA-SUM  | 20,655,776       | 48,217,560                  | 71,342,952            |
| SERVER-AVG-DISK-SPACEK-USAGE          | 2.6 GB           | 10 GB                       | 2.9 GB                |
