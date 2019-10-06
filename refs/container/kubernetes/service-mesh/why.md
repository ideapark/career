# Why We Need Service Mesh

A service mesh is a dedicated infrastructure layer for handling
service-to-service communication. It's responsible for the reliable delivery of
requests the complex topology of services that comprise a modern, cloud native
application.

In the cloud native model, a single application might consist of hundreds of
services; each service might have thousands of instances; and each of those
instances might be in a constantly-changing state as they are dynamically
scheduled by an orchestrator like Kubernetes. Not only is service communication
in this world incredibly complex, it's a pervasive and fundamental part of
runtime behavior. Managing it is vital to ensuring end-to-end performance and
reliability.
