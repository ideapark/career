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

# oc administrator cli operations

| Basic CLI Operations              | Description                    |
| ---                               | ---                            |
| oc adm new-project <project_name> | Creates a new project          |
| oc adm policy                     | Manages authorization policies |
| oc adm groups                     | Manages groups                 |

| Install CLI Operations                | Description                                      |
| ---                                   | ---                                              |
| oc adm router <router_name>           | Installs a router                                |
| oc adm ipfailover <ipfailover_config> | Installs an IP failover group for a set of nodes |
| oc adm registry                       | Installs an integrated container image registry  |

| Maintenance CLI Operations                | Description                                                           |
| ---                                       | ---                                                                   |
| oc adm build-chain <image_stream>[:<tag>] | Outputs the inputs and dependencies of any builds                     |
| oc adm manage-node                        | Manages nodes. For example, list or evacuate pods, or mark them ready |
| oc adm prune                              | Removes older versions of resources from the server                   |

| Settings CLI Operations         | Description                                                         |
| ---                             | ---                                                                 |
| oc adm config <subcommand>      | Changes kubelet configuration files                                 |
| oc adm create-kubeconfig        | Creates a basic .kubeconfig file from client certificates           |
| oc adm create-api-client-config | Creates a configuration file for connecting to the server as a user |

| Advanced CLI Operations                  | Description                               |
| ---                                      | ---                                       |
| oc adm create-bootstrap-project-template | Creates a bootstrap project template      |
| oc adm create-bootstrap-policy-file      | Creates the default bootstrap policy      |
| oc adm create-login-template             | Creates a login template                  |
| oc adm create-node-config                | Creates a configuration bundle for a node |
| oc adm ca                                | Manages certificates and keys             |
