# StatefulSet

Deployments and ReplicaSets is designed for headless service, StatefulSet is
used to solve stateful service.

- Stable persistent storage, PVC
- Stable network, PodName and HostName stay unchanged, implemented by HeadlessService
- Sequence deployment/downline, implemented by init containers
