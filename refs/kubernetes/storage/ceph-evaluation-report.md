# Ceph 评估报告

## Ceph 架构原理

## Ceph 性能测试

### Cluster

CentOS VM: 2-cpu 4G-mem 8G-disk

192.168.3.31 ceph-client
192.168.3.32 ceph-admin
192.168.3.33 ceph-storage1
192.168.3.34 ceph-storage2
192.168.3.35 ceph-storage3

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
