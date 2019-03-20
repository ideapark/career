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

# output verbosity and debugging

| Verbosity | Description                                                                                                                                                                                      |
| ---       | ---                                                                                                                                                                                              |
| --v=0     | Generally useful for this to ALWAYS be visible to an operator.                                                                                                                                   |
| --v=1     | A reasonable default log level if you don't want verbosity.                                                                                                                                      |
| --v=2     | Useful steady state information about the service and important log messages that may correlate to significant changes in the system. This is the recommended default log level for most system. |
| --v=3     | Extended information about changes.                                                                                                                                                              |
| --v=4     | Debug level verbosity.                                                                                                                                                                           |
| --v=6     | Display requested resources.                                                                                                                                                                     |
| --v=7     | Display HTTP request headers.                                                                                                                                                                    |
| --v=8     | Display HTTP request contents.                                                                                                                                                                   |
| --v=9     | Display HTTP request contents without truncation of contents.                                                                                                                                    |
