# oc reference card

| Object Type           | Abbreviated Version |
|-----------------------|---------------------|
| build                 |                     |
| buildConfig           | bc                  |
| deploymentConfig      | dc                  |
| event                 | ev                  |
| imageStream           | is                  |
| imageStreamTag        | istag               |
| imageStreamImage      | isimage             |
| job                   |                     |
| LimitRange            | limits              |
| node                  |                     |
| pod                   | po                  |
| ResourceQuota         | quota               |
| replicationController | rc                  |
| secrets               |                     |
| service               | svc                 |
| ServiceAccount        | sa                  |
| persistentVolume      | pv                  |
| persistentVolumeClaim | pvc                 |

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
