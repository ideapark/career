# Ceph 评估报告

## Ceph 架构原理

```text
  +--------------------------------------+
  |              HOST/VM                 |
  +--------------------------------------+
     +-------------------------------+
     |           librbd              |
     +-------------------------------+
         +----------------------+
         |       librados       |
         +----------------------+
                   |socket
                   |
+---+---+---+---+---+---+---+---+---+---+
|osd|osd|osd|osd|ods|ods|ods|mds|ods|ods|
+---+---+---+---+---+---+---+---+---+---+
+---+---+---+---+---+---+---+---+---+---+
|osd|osd|mon|osd|ods|ods|ods|rgw|ods|ods|
+---+---+---+---+---+---+---+---+---+---+
+---+---+---+---+---+---+---+---+---+---+
|osd|mds|osd|osd|ods|mon|ods|ods|ods|ods|
+---+---+---+---+---+---+---+---+---+---+
+---+---+---+---+---+---+---+---+---+---+
|osd|rgw|osd|osd|ods|ods|ods|ods|mon|ods|
+---+---+---+---+---+---+---+---+---+---+
```

## CEPH 性能测试

### Test Cluster (CentOS Ceph Cluster)

| Host Name | IP (192.168.0.0/24) | Ceph Service |
|-----------|---------------------|--------------|
| client    |       192.168.3.100 | N/A          |
| node0     |       192.168.3.101 | osd,mon,mgr  |
| node1     |       192.168.3.102 | osd,mon,rgw  |
| node2     |       192.168.3.103 | osd,mon,rgw  |
| node3     |       192.168.3.104 | osd,mds      |

### Benchmark Baseline

- Disk

dd if=/dev/zero of=here bs=1G count=1 oflag=direct

- Network

iperf -s               # host1
iperf -c 192.168.1.1   # host2

### Benchmark

- Drop caches

sudo echo 3 | sudo tee /proc/sys/vm/drop_caches && sudo sync

## 业界应用情况

## 结论
