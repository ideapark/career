#!/usr/bin/bash

# This script instructs how to bootstrap ceph cluster using docker container and
# test ceph's services.

# Cluster Info
#
# +------------+----------------------+--------------------+----------------+
# | Host Name  | IP (192.168.99.0/24) |   Disk             |  Ceph Service  |
# +------------+----------------------+--------------------+----------------+
# | client     | 192.168.99.100       | /dev/{sda,sdb,sdc} | N/A            |
# | node0      | 192.168.99.101       | /dev/{sda,sdb,sdc} | mon,osd*2,mgr  |
# | node1      | 192.168.99.102       | /dev/{sda,sdb,sdc} | mon,osd*2,rgw  |
# | node2      | 192.168.99.103       | /dev/{sda,sdb,sdc} | mon,osd*2,mds  |
# | node3      | 192.168.99.104       | /dev/{sda,sdb,sdc} |     osd*2,mds  |
# +------------+----------------------+--------------------+----------------+

# node0
#
# Run our first monitor
read cmd <<EOF
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e MON_IP=192.168.99.101 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
ssh -t node0 $cmd

# node0
#
# Distribute /etc/ceph,/var/lib/ceph to node1,node2,node3
#
# NOTE: root permission required
read cmd <<EOF
for node in node1 node2 node3
do
    scp -r /etc/ceph     ${node}:/etc
    scp -r /var/lib/ceph ${node}:/var/lib
done
EOF
ssh -t node0 $cmd

# node1
#
# Run second monitor
read cmd <<EOF
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e MON_IP=192.168.99.102 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
ssh -t node1 $cmd

# node2
#
# Run third monitor
read cmd <<EOF
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e MON_IP=192.168.99.103 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
ssh -t node2 $cmd

# node0
#
# Run a ceph manager
read cmd <<EOF
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       ceph/daemon mgr
EOF
ssh -t node0 $cmd

# node0,node1,node2,node3
#
# Run 2 osds (Object Storage Daemon) on each node
read cmd <<EOF
# destroy partition table if needed
docker run --rm -d --privileged=true \
       -v /dev:/dev \
       -e OSD_DEVICE=/dev/sdb \
       ceph/daemon zap_device

# ===> osd on /dev/sdb
docker run -d --net=host \
       --pid=host \
       --privileged=true \
       -v /dev:/dev \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e OSD_DEVICE=/dev/sdb \
       ceph/daemon osd

# destroy partition table if needed
docker run --rm -d --privileged=true \
       -v /dev:/dev \
       -e OSD_DEVICE=/dev/sdc \
       ceph/daemon zap_device

# ===> osd on /dev/sdc
docker run -d --net=host \
       --pid=host \
       --privileged=true \
       -v /dev:/dev \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e OSD_DEVICE=/dev/sdc \
       ceph/daemon osd
EOF
for node in node0 node1 node2 node3
do
    ssh -t ${node} ${cmd}
done

# node2,node3
#
# Run 2 mds (Metadata Server)
read cmd <<EOF
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       -e CEPHFS_CREATE=1 \
       ceph/daemon mds
EOF
for node in node2 node3
do
    ssh -t ${node} ${cmd}
done

# node1
#
# Run a rgw (Rados Gateway)
# NOTE: expose container port 8080 to host 80 port
read cmd <<EOF
docker run -d -p 80:8080 \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph:/var/lib/ceph \
       ceph/daemon rgw
EOF
ssh -t node1 $cmd

exit 0

# DEBUG:
#   stop and remove ceph containers
#   delete /etc/ceph,/var/lib/ceph
read cmd <<EOF
docker stop \$(docker ps -aq)
docker rm   \$(docker ps -aq)
rm -rf /etc/ceph
rm -rf /var/lib/ceph
EOF
for node in node0 node1 node2 node3
do
    ssh -t ${node} ${cmd}
done
