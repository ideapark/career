# playbooks run in the order

| Playbook Name                            | File Location                                                           |
| ---------------------------------------- | ----------------------------------------------------------------------- |
| Health Check                             | ~/opeshift-ansible/playbooks/openshift-checks/pre-install.yml           |
| Node Bootstrap                           | ~/opeshift-ansible/playbooks/openshift-node/bootstrap.yml               |
| etcd Install                             | ~/opeshift-ansible/playbooks/openshift-etcd/config.yml                  |
| NFS Install                              | ~/opeshift-ansible/playbooks/openshift-nfs/config.yml                   |
| Load Balancer Install                    | ~/opeshift-ansible/playbooks/openshift-loadbalancer/config.yml          |
| Master Install                           | ~/opeshift-ansible/playbooks/openshift-master/config.yml                |
| Master Additional Install                | ~/opeshift-ansible/playbooks/openshift-master/additional_config.yml     |
| Node Join                                | ~/opeshift-ansible/playbooks/openshift-node/join.yml                    |
| GlusterFS Install                        | ~/opeshift-ansible/playbooks/openshift-glusterfs/config.yml             |
| Hosted Intall                            | ~/opeshift-ansible/playbooks/openshift-hosted/config.yml                |
| Monitoring Install                       | ~/opeshift-ansible/playbooks/openshift-monitoring/config.yml            |
| Web Console Install                      | ~/opeshift-ansible/playbooks/openshift-web-console/config.yml           |
| Admin Console Install                    | ~/opeshift-ansible/playbooks/openshift-console/config.yml               |
| Metrics Install                          | ~/opeshift-ansible/playbooks/openshift-metrics/config.yml               |
| Logging Install                          | ~/opeshift-ansible/playbooks/openshift-logging/config.yml               |
| Availability Monitoring Install          | ~/opeshift-ansible/playbooks/openshift-monitor-availability/config.yml  |
| Service Catalog Install                  | ~/opeshift-ansible/playbooks/openshift-service-catalog/config.yml       |
| Management Install                       | ~/opeshift-ansible/playbooks/openshift-management/config.yml            |
| Descheduler Install                      | ~/opeshift-ansible/playbooks/openshift-descheduler/config.yml           |
| Node Problem Detector Install            | ~/opeshift-ansible/playbooks/openshift-node-problem-detector/config.yml |
| Autoheal Install                         | ~/opeshift-ansible/playbooks/openshift-autoheal/config.yml              |
| Operator Lifecycle Manager (OLM) Install | ~/opeshift-ansible/playbooks/olm/config.yml                             |
