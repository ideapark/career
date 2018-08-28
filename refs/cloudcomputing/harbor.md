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

# Implementation

## docker login

```bash
docker login 192.168.1.10
```

```text
                                             4  +----------+   5  +----------+
                                          +---->| ui/token |----->| database |
                      1                   |     +----------+      +----------+
+---------------+ --------> +-------+     |
| Docker client |           | proxy |-----+
+---------------+ --------> +-------+     |  2  +----------+
                      3                   +---->| registry |
                                                +----------+
```

(1) First, this request is received by the proxy container listening on port 80.
Nginx in the container forwards the request to the Registry container at the
backend.

(2) The Registry container has been configured for token-based authentication,
so it returns an error code 401, notifying the Docker client to obtain a valid
token from a specified URL. In Harbor, this URL points to the token service of
Core Services.

(3) When the Docker client receives this error code, it sends a request to the
token service URL, embedding username and password in the request header
according to basic authentication of HTTP specification.

(4) After this request is sent to the proxy container via port 80, Nginx again
forwards the request to the UI container according to pre-configured rules. The
token service within the UI container receives the request, it decodes the
request and obtains the username and password.

(5) After getting the username and password, the token service checks the
database and authenticates the user by the data in the MySQL database. When the
token service is configured for LDAP/AD authentication, it authenticates against
the external LDAP/AD server. After a successful authentication, the token
service returns a HTTP code that indicates the success. The HTTP response body
contains a token generated by a private key.

At this point, one docker login process has been completed. The Docker client
saves the encoded username/password from step (3) locally in a hidden file.

## docker push

```bash
docker push 192.168.1.10/library/hello-world
```

```text
                                       +-----------+  3   +----------+
                                      /|  ui/token |----->| database |
                                   2 / +-----------+      +----------+
                                    /
+---------------+ ------> +-------+/
| Docker client |         | Proxy |\
+---------------+ <------ +-------+\\ 1
                                  4 \\
                                     \\+----------+
                                      \| registry |
                                       +----------+
```

(1) Firstly, the docker client repeats the process similar to login by sending
the request to the registry, and then gets back the URL of the token service.

(2) Subsequently, when contacting the token service, the Docker client provides
additional information to apply for a token of the push operation on the image
(library/hello-world).

(3) After receiving the request forwarded by Nginx, the token service queries
the database to look up the user's role and permissions to push the image. If
the user has the proper permission, it encodes the information of the push
operation and signs it with a private key and generates a token to the Docker
client.

(4) After the Docker client gets the token, it sends a push request to the
registry with a header containing the token. Once the Registry receives the
request, it decodes the token with the public key and validates its content. The
public key corresponds to the private key of the token service. If the registry
finds the token valid for pushing the image, the image transferring process
begins.
