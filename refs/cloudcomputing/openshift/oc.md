# oc reference card

| Object Type           | Abbreviated Version |
|-----------------------|---------------------|
| Build                 |                     |
| BuildConfig           | bc                  |
| DeploymentConfig      | dc                  |
| Event                 | ev                  |
| ImageStream           | is                  |
| ImageStreamTag        | istag               |
| ImageStreamImage      | isimage             |
| Job                   |                     |
| CronJob               | cj                  |
| LimitRange            | limits              |
| Node                  |                     |
| Pod                   | po                  |
| ResourceQuota         | quota               |
| ReplicationController | rc                  |
| ReplicaSet            | rs                  |
| Secrets               |                     |
| Service               | svc                 |
| ServiceAccount        | sa                  |
| StatefulSets          | sts                 |
| PersistentVolume      | pv                  |
| PersistentVolumeClaim | pvc                 |

[1]: If you want to know the full list of resources the server supports, use `oc api-resources`

# Troubleshooting oc

You can get more verbosed output from any command by increasing the loglevel
using -v=X flag. By default, the loglevel is set to 0, but you can set its value
from 0 to 10.

1-5 - are usually used internally by the commands, if the author decides to provide more explanation about the flow.
  6 - provides basic information about HTTP traffic between the client and the server, such HTTP operation and URL.
  7 - provides more thorough HTTP information, such as HTTP operation, URL, request headers and response status code.
  8 - provides full HTTP request and response, including body.
  9 - provides full HTTP request and response, including body and sample curl invocation.
 10 - provides all possible output the command provides.
