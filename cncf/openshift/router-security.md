# Secured routes

- edge

The secure connection is terminated by the router, with the router proxying the
connection to the application using an insecure connection over the internal
cluster network. If not supplying your own hostname and SSL certificate, the SSL
certificate of the OpenShift cluster will be used. Although an insecure
connection is used internally, the traffic is not visible to other users of the
cluster.

- passthrough

The router will proxy the secure connection directly through to the application.
The application must be able to accept a secure connection and be configured
with the appropriate SSL certificate. Provided that the client supports Server
Name Identification (SNI) over a Transport Layer Security (TLS) connection, this
can be used to allow access to an application using non-HTTP protocols.

- reencrypt

The secure connection is terminated by the route, with the router re-encrypting
traffic when proxying the connection to the application. If not supplying your
own hostname and SSL certificate, the SSL certificate of the OpenShift cluster
will be used for the initial inbound connection. For the connection from the
router to the application, the application must be able to accept a secure
connection and be configured with the appropriate SSL certificate used for the
re-encrypted connection.
