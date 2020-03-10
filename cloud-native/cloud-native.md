---
author: Zhou Peng <p@ctriple.cn>
description: cloud-native pillars and levels
---
# Cloud-Native Pillars & Capability Level

## 4 Pillars

```text
S C A L A B L E            R E S I L L I E N T       O B S E R V A B L E        S E C U R I T Y
 Horizontal AutoScaler       Retry                     Monitoring                 Authentication
 High Availability           Timeout                   Logging                    Authorization
                             Circuit Breaker           Metrics                    Audit
                             Load Balance              Tracing                    mTLS
------------------------------------------------------------------------------------------------
                                            API DRIVEN
```

## 2 Capability Level

- As Code: Versioned, Repeatable (Ansible, Terraform)
- As Software: API driven, Self-Awareness, Auto-Pilot (Kubernetes, Operator)
