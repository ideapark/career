# ServiceAccount

- UserAccount is used to authenticate people, ServiceAccount is used for process
  to call Kubernetes API

- UserAccount across namespaces, ServiceAccount limited to one namespace

- A default SericeAccount created automatically for every namespace

- TokenController detects ServiceAccount and create Secret

- ServiceAccount AdmissionController
  - Pod will be set a default ServiceAccount
  - Test ServiceAccount referenced by Pod exists
  - If Pod did not specify ImagePullSecrets, use ServiceAccount's ImagePullSecrets
  - ServiceAccount's ca.crt will be mounted to /var/run/secrets/kubernetes.io/serviceaccount after container started.
