#!/usr/bin/bash

# This script instructs how to bootstrap ceph cluster using docker container and
# test ceph's services.

# Cluster Info
#
# +------------+-----------------+--------------------+----------------+
# | Host Name  |    IP           |   Disk             |  Ceph Service  |
# +------------+-----------------+--------------------+----------------+
# | client     | 192.168.99.100  | /dev/{sda,sdb,sdc} | N/A            |
# | node0      | 192.168.99.101  | /dev/{sda,sdb,sdc} | mon,osd*2,mgr  |
# | node1      | 192.168.99.102  | /dev/{sda,sdb,sdc} | mon,osd*2,rgw  |
# | node2      | 192.168.99.103  | /dev/{sda,sdb,sdc} | mon,osd*2,mds  |
# | node3      | 192.168.99.104  | /dev/{sda,sdb,sdc} |     osd*2,mds  |
# +------------+-----------------+--------------------+----------------+

# node0:
#
# Run our first monitor
sudo docker run -d --net=host \
     -v /etc/ceph:/etc/ceph \
     -v /var/lib/ceph:/var/lib/ceph \
     -e MON_IP=192.168.99.101 \
     -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
     ceph/daemon mon

# node0
#
# Distribute /etc/ceph,/var/lib/ceph to node1,node2,node3
#
# NOTE: root permission required
for node in node1 node2 node3
do
    scp -r /etc/ceph     root@${node}:/etc
    scp -r /var/lib/ceph root@${node}:/var/lib
done

# node1
#
# Run second monitor
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e MON_IP=192.168.99.102 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon

# node2
#
# Run third monitor
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e MON_IP=192.168.99.103 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon

# node0
#
# Run a ceph manager
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       ceph/daemon mgr

# node0,node1,node2,node3
#
# Run 2 osds on each node

# ===> osd on /dev/sdb
docker run -d --net=host \
       --privileged=true \
       -v /dev:/dev \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e OSD_FORCE_ZAP=1 \
       -e OSD_DEVICE=/dev/sdb \
       ceph/daemon osd_ceph_disk

# ===> osd on /dev/sdc
docker run -d --net=host \
       --privileged=true \
       -v /dev:/dev \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e OSD_FORCE_ZAP=1 \
       -e OSD_DEVICE=/dev/sdc \
       ceph/daemon osd_ceph_disk

# node2,node3
#
# Run 2 mds
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e CEPHFS_CREATE=1 \
       ceph/daemon mds

# node1
#
# Run a rgw (Rados Gateway)
# NOTE: expose container port 8080 to host 80 port
docker run -d -p 80:8080 \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       ceph/daemon rgw
