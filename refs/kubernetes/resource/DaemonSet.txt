# DaemonSet

DaemonSet ensure containers running on every cluster node, such as cluster
logging, monitoring, and other system management tasks.

- Collecting Log: fluentd, logstash
- System Monitor: Prometheus Node Exporter, collected, New Relic agent, Ganglia gmond
- System Process: kube-proxy, kube-dns, glusterd, ceph
