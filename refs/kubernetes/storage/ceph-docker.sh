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

# trap ctrl-c and call reset_cluster()
trap reset_cluster INT

function reset_cluster() {
    (cat <<'EOF'
# destroy partition table: '/dev/sdb'
docker run --rm -d --privileged=true \
       -v /dev/:/dev/ \
       -e OSD_DEVICE=/dev/sdb \
       ceph/daemon zap_device

# destroy partition table: '/dev/sdc'
docker run --rm -d --privileged=true \
       -v /dev/:/dev/ \
       -e OSD_DEVICE=/dev/sdc \
       ceph/daemon zap_device

docker stop $(docker ps -aq)
docker rm   $(docker ps -aq)

rm -rf /etc/ceph/
rm -rf /var/lib/ceph/
EOF
    ) > $CMD
    for node in node0 node1 node2 node3
    do
        ssh -t ${node} 'bash -s' < $CMD
    done
}

CMD=/tmp/ceph.cmd

# node0
#
# Run our first monitor
(cat <<'EOF'
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e MON_IP=192.168.99.101 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
) > $CMD
ssh -t node0 'bash -s' < $CMD

read -p 'confirm mon initialized ok, continue? '

# node0
#
# Distribute /etc/ceph,/var/lib/ceph to node1,node2,node3
#
# NOTE: root permission required
(cat <<'EOF'
for node in node1 node2 node3
do
    scp -r /etc/ceph/     ${node}:/etc/
    scp -r /var/lib/ceph/ ${node}:/var/lib/
done
EOF
) > $CMD
ssh -t node0 'bash -s' < $CMD

# node1
#
# Run second monitor
(cat <<'EOF'
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e MON_IP=192.168.99.102 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
) > $CMD
ssh -t node1 'bash -s' < $CMD

read -p 'confirm mon initialized ok, continue? '

# node2
#
# Run third monitor
(cat <<'EOF'
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e MON_IP=192.168.99.103 \
       -e CEPH_PUBLIC_NETWORK=192.168.99.0/24 \
       ceph/daemon mon
EOF
) > $CMD
ssh -t node2 'bash -s' < $CMD

read -p 'confirm mon initialized ok, continue? '

# node0
#
# Run a ceph manager
(cat <<'EOF'
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       ceph/daemon mgr
EOF
) > $CMD
ssh -t node0 'bash -s' < $CMD

read -p 'confirm mgr initialized ok, continue? '

# node0,node1,node2,node3
#
# Run 2 osds (Object Storage Daemon) on each node
(cat <<'EOF'
# ===> osd on /dev/sdb
docker run -d --net=host \
       --pid=host \
       --privileged=true \
       -v /dev/:/dev/ \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e OSD_DEVICE=/dev/sdb \
       ceph/daemon osd

# ===> osd on /dev/sdc
docker run -d --net=host \
       --pid=host \
       --privileged=true \
       -v /dev/:/dev/ \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e OSD_DEVICE=/dev/sdc \
       ceph/daemon osd
EOF
) > $CMD
for node in node0 node1 node2 node3
do
    ssh -t ${node} 'bash -s' < $CMD
done

read -p 'confirm osds initialized ok, continue? '

# node2,node3
#
# Run 2 mds (Metadata Server)
(cat <<'EOF'
docker run -d --net=host \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       -e CEPHFS_CREATE=1 \
       ceph/daemon mds
EOF
) > $CMD
for node in node2 node3
do
    ssh -t ${node} 'bash -s' < $CMD
done

read -p 'confirm mds initialized ok, continue? '

# node1
#
# Run a rgw (Rados Gateway)
# NOTE: expose container port 8080 to host 80 port
(cat <<'EOF'
docker run -d -p 80:8080 \
       -v /etc/ceph:/etc/ceph \
       -v /var/lib/ceph/:/var/lib/ceph/ \
       ceph/daemon rgw
EOF
) > $CMD
ssh -t node1 'bash -s' < $CMD

read -p 'confirm rgw initialized ok, continue? '

# DEBUG:
#   stop and remove ceph containers
#   delete /etc/ceph,/var/lib/ceph
read -p '===>> RESET CLUSTER (YES)? ' RESET

if [ "YES" != "$RESET" ]
then
    exit 0
fi

reset_cluster

exit 1
