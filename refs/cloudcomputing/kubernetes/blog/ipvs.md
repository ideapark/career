# IPVS-Based In-Cluster Load Balancing

- kube-proxy --ipvs-scheduler

  rr: round-robin
  lc: least connection
  dh: destination hashing
  sh: source hashing
  sed: shortest expected delay
  nq: never queue

- ipvs service network topology

  1. Make sure a dummy interface exists in the node, defaults to kube-ipvs0
  2. Binding Service IP addresses to the dummy interface
  3. Create IPVS virtual servers for each Service IP address respectively

- Usage Example

```bash
# kubectl describe svc nginx-service
Name:			nginx-service
...
Type:               ClusterIP
IP:                 10.102.128.4
Port:               http	3080/TCP
Endpoints:          10.244.0.235:8080,10.244.1.237:8080
Session Affinity:   None

# ip addr
...
73: kube-ipvs0: <BROADCAST,NOARP> mtu 1500 qdisc noop state DOWN qlen 1000
    link/ether 1a:ce:f5:5f:c1:4d brd ff:ff:ff:ff:ff:ff
    inet 10.102.128.4/32 scope global kube-ipvs0
       valid_lft forever preferred_lft forever

# ipvsadm -ln
IP Virtual Server version 1.2.1 (size=4096)
Prot LocalAddress:Port Scheduler Flags
  -> RemoteAddress:Port           Forward Weight ActiveConn InActConn
TCP  10.102.128.4:3080 rr
  -> 10.244.0.235:8080            Masq    1      0          0
  -> 10.244.1.237:8080            Masq    1      0          0
```

- Iptables & Ipset in IPVS Proxier

IPVS is for load balancing and it can't handle other workarounds in kube-proxy,
e.g. packet filtering, hairpin-masquerade, SNAT, etc. IPVS proxier leverages
iptables in the above scenarios. Specifically, ipvs proxier will fall back on
iptables in the following 4 scenarios:

  1. kube-proxy start with --masquerade-all=true
  2. Specify cluster CIDR in kube-proxy startup
  3. Support LoadBalancer type service
  4. Support NodePort type service

However, we don’t want to create too many iptables rules. So we adopt ipset for
the sake of decreasing iptables rules. The following is the table of ipset sets
that IPVS proxier maintains:

| SET NAME                       | MEMBERS                                                          | USAGE                                                                                 |
| ------------------------------ | ---------------------------------------------------------------- | ------------------------------------------------------------------------------------- |
| KUBE-CLUSTER-IP                | All Service IP + port                                            | masquerade for cases that masquerade-all=true or clusterCIDR specified                |
| KUBE-LOOP-BACK                 | All Service IP + port +IP                                        | masquerade for resolving hairpin issue                                                |
| KUBE-EXTERNAL-IP               | Service External IP + port                                       | masquerade for packets to external IPs                                                |
| KUBE-LOAD-BALANCER-LOCAL       | Load Balancer ingress IP + port with externalTrafficPolicy=local | accept packets to Load Balancer with externalTrafficPolicy=local                      |
| KUBE-LOAD-BALANCER-FW          | Load Balancer ingress IP + port with loadBalancerSourceRanges    | Drop packets for Load Balancer Service with loadBalancerSourceRanges specified        |
| KUBE-LOAD-BALANCER-SOURCE-CIDR | Load Balancer ingress IP + port + source CIDR                    | accept packets for Load Balancer type Service with loadBalancerSourceRanges specified |
| KUBE-NODE-PORT-TCP             | NodePort type Service TCP port                                   | masquerade for packets to NodePort(TCP)                                               |
| KUBE-NODE-PORT-LOCAL-TCP       | NodePort Service TCP port with externalTrafficPolicy=local       | accept packets to NodePort Service with externalTrafficPolicy=local                   |
| KUBE-NODE-PORT-UDP             | NodePort type Service UDP port                                   | masquerade for packets to NodePort(UDP)                                               |
| KUBE-NODE-PORT-LOCAL-UDP       | NodePort type service UDP port with externalTrafficPolicy=local  | accept packets to NodePort Service with externalTrafficPolicy=local                   |
