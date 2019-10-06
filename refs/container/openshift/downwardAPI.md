# Downward API

The downward API is a mechanism that allows containers to consume information
about API objects without coupling to OKD. Such information includes the pod's
name, namespace, and resource values. Containers can consume information from
the downward API using environment variables or a valume plug-in.

Fields within the pod are selected using the FieldRef API type. FieldRef has two
fields:

| Field      | Description                                                |
| ---        | ---                                                        |
| fieldPath  | The path of the field to select, relative to the pod.      |
| apiVersion | The API version to interpret the filePath selector within. |

Currently, the valid selectors in the v1 API include:

| Selector             | Description                                                                                |
| ---                  | ---                                                                                        |
| metadata.name        | The pod's name. This is supported in both environment variables and volumes.               |
| metadata.namespace   | The pod's namespace. This is supported in both environment variables and volumes.          |
| metadata.labels      | The pod's labels. This is only supported in volumes and not in environment variables.      |
| metadata.annotations | The pod's annotations. This is only supported in volumes and not in environment variables. |
| status.podIP         | The pod's IP. This is only supported in environment variables and not volumes.             |

The apiVersion field, if not specified, defaults to the API version of the
enclosing pod template.

```yaml
kind: Pod
apiVersion: v1
metadata:
  labels:
    zone: us-east-coast
    cluster: downward-api-test-cluster1
    rack: rack-123
  name: dapi-volume-test-pod
  annotations:
    annotation1: "345"
    annotation2: "456"
spec:
  containers:
    - name: volume-test-container
      image: gcr.io/google_containers/busybox
      command: ["sh", "-c", "cat /tmp/etc/pod_labels /tmp/etc/pod_annotations"]
      volumeMounts:
        - name: podinfo
          mountPath: /tmp/etc
          readOnly: false
  volumes:
  - name: podinfo
    downwardAPI:
      defaultMode: 420
      items:
      - fieldRef:
          fieldPath: metadata.name
        path: pod_name
      - fieldRef:
          fieldPath: metadata.namespace
        path: pod_namespace
      - fieldRef:
          fieldPath: metadata.labels
        path: pod_labels
      - fieldRef:
          fieldPath: metadata.annotations
        path: pod_annotations
```
