# StatefulSet

Deployments and ReplicaSets is designed for headless service, StatefulSet is
used to solve stateful service.

- Stable persistent storage, PVC
- Stable network, PodName and HostName stay unchanged, implemented by HeadlessService
- Sequence deployment/downline, implemented by init containers

```text
  StatefulSet:
                #
       CREATE   #- Pod-0
            |   #
            |   #- Pod-1
            |   #
            |   #- Pod-2
            V   #
                #- Pod-3 <---- partition = 3
            ^   #
            |   #- Pod-4
            |   #
            |   #- Pod-5
            |   #
    TERMINATE   #- Pod-6
                #
                #- Pod-n
                V
```
