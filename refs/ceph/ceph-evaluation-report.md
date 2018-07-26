# Ceph 评估报告

## Ceph 架构原理

### 架构

![Ceph Architecture](img/ceph-architecture.png)

### 存储节点

![Ceph OSD](img/ceph-osd-internals.png)

### Rados 接口

![Rados](img/ceph-rados.png)

### 块存储

#### 虚拟机
![Ceph Block Device for VM](img/ceph-rbd-vm.png)

#### 主机
![Ceph Block Device for Host](img/ceph-rbd-host.png)

### 对象存储

![Ceph Object Storage](img/ceph-rgw.png)

### 文件系统

![Ceph Filesystem](img/ceph-fs.png)

## CEPH 性能测试

### Test Cluster (CentOS Ceph Cluster)

| Host Name | IP (192.168.0.0/24) | Disk           | Ceph Service |
| --------- | ------------------- | -------------  | ------------ |
| client    |       192.168.3.100 | /dev/{sda,sdb} | N/A          |
| node0     |       192.168.3.101 | /dev/{sda,sdb} | osd,mon,mgr  |
| node1     |       192.168.3.102 | /dev/{sda,sdb} | osd,mon,rgw  |
| node2     |       192.168.3.103 | /dev/{sda,sdb} | osd,mon,rgw  |
| node3     |       192.168.3.104 | /dev/{sda,sdb} | osd,mds      |

### Benchmark Baseline

- Disk

dd if=/dev/zero of=here bs=1G count=1 oflag=direct

- Network

iperf -s               # host1
iperf -c 192.168.1.1   # host2

### Benchmark

- Drop caches

sudo echo 3 | sudo tee /proc/sys/vm/drop_caches && sudo sync

#### rados

```bash
rados bench -p <poolname> 10 write --no-cleanup
rados bench -p <poolname> 10 seq
rados bench -p <poolname> 10 rand
```

#### rbd

```bash
rbd bench --io-type write <imagename> --pool=<poolname>
rbd bench --io-type read  <imagename> --pool=<poolname>
```

#### rgw

```bash
radosgw-admin user create --uid=benchmark --display-name="benchmark"
radosgw-admin subuser create --uid=benchmark --subuser=benchmark:swift --access=full
radosgw-admin key create --subuser=benchmark:swift --key-type=swift --secret=guessme
radosgw-admin user modify --uid=benchmark --max-buckets=0
```

- swift.conf

```text
[bench]
auth = http://ip:port/auth/v1.0
user = benchmark:swift
key = guessme
auth_version = 1.0
```

```bash
swift-bench -c 64 -s 4096 -n 1000 -g 100 swift.conf
```

#### cephfs

```bash
# kernel module support
modinfo  ceph
modprobe ceph

mkdir ~/mycephfs
mount -t ceph monitor-ip:/ ~/mycephfs
```
