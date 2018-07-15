# Ceph 评估报告

## Ceph 架构原理

## Ceph 性能测试

### Test Cluster (CentOS Ceph Cluster)

http://docs.ceph.org.cn/start/quick-start-preflight/

 admin-node: 192.168.3.30 +-----------> node1: 192.168.3.31
               ceph-deploy|             mon.node1
                          |
                          +-----------> node2: 192.168.3.32
                          |             osd.0
                          |
                          +-----------> node3: 192.168.3.33
                                        osd.1

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
