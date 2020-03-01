# Cloud-Native Application Request/Response Tracing


- Tracing Visualization

```text
+-----------------------------------------------------------------------------+
| Client transaction from start to end                                        |
+-----------------------------------------------------------------------------+
     | LoadBalancer transaction from start to end                             |
     +------------------------------------------------------------------------+
       +-------------+
       | Authn/Authz |
       +-------------+
                      +---------+
                      | Billing |
                      +---------+
                                 +--------------------------------------------+
                                 | Resource allocation and provisioning       |
                                 +--------------------------------------------+
                                    +--------------------+
                                    | Container start-up |
                                    +--------------------+
                                    +--------------------+
                                    | Storage allocation |
                                    +--------------------+
                                                           +------------------+
                                                           | Start-up scripts |
                                                           +------------------+
Time
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
```

- Futher Thinking

As to kubernetes network plugin, although overlayed network type (such as vxlan,
openvsiwtch) introduce ~30% performance degrade, the whole request/response
delay may not have significiently impact.
