# Harbor

```text
                   +-------------------------------------------------------+
                   |                     +---------------+                 |
                   |                +--->| Core services |                 |
                   |                |    | +-----------+ |                 |
                   |                |    | |     UI    | |    +----------+ |
                   |   +-------+    |    | +-----------+ |--->| Database | |
 Docker Client ------> | Proxy |--->|    | |   token   | |    +----------+ |
 Browser           |   +-------+    |    | +-----------+ |           |     |
                   |                |    | |  webhook  | |           |     |
                   |                |    | +-----------+ |           |     |
                   |                |    +---------------+ \         |     |
                   |                |           |           \        |     |
                   |                |           |            \       |     |
                   |                |    +----------+     +--------------+ |     Replicate to
                   |                +--->| Registry |---->| Job Services |-----> remote Harbor
                   |                     +----------+     +--------------+ |
                   +-------------------------------------------------------+
                                               |
                                               | Log
                                               |
                                       +---------------+
                                       | Log Collector |
                                       +---------------+
```

## Proxy

Components of Harbor, such as registry, UI and token services, are all behind a
reversed proxy. The proxy forwards requests from browsers and Docker clients to
various backend services.

## Registry

Responsible for storing Docker images and processing Docker push/pull commands.
As Harbor needs to enforce access control to images, the Registry will direct
clients to a token service to obtain a valid token for each pull or push
request.

## Core services

Harbor's core functions, wich mainly provides the following services:

- UI

a graphical user interface to help users manage images on the Registry

- Webhook

webhook is a mechanism configured in the Registry so that image status changes
in the Registry can be populated to the webhook endpoint of Harbor. Harbor uses
webhook to update logs, initiate replications, and some other functions.

- Token service

responsible for issuing a token for every docker pull/push command according to
a user's role of a project. If there is no token in a request sent from a Docker
client, the Registry will redirect the request to the token service.

- Database

database stores the meta data of projects, users, roles, replication policies
and images.

- Job services

used for image replication, local images can be replicated (synchronized) to
other Harbor instances.

- Log collector

responsible for collecting logs of other modules in a single place.
