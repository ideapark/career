# service

A Kubernetes service serves as an internal load balancer. It identifies a set of
replicated pods in order to proxy the connections it receives to them. Backing
pods can be added to or removed from a service arbitrarily while the service
remains consistently available, enabling anything that depends on the service to
refer to it at a consistent address. The default service clusterIP addresses are
from the OpenShift Online internal network and they are used to permit pods to
access each other.

Services are assigned an IP address and port pair that, when accessed, proxy to
an appropriate backing pod. A service uses a label selector to find all the
containers running that provide a certain network service on a certain port.

# headless service

If your application does not need load balancing or single-service IP addresses,
you can create a headless service. When you create a headless service, no
load-balancing or proxying is done and no cluster IP is allocated for this
service. For such services, DNS is automatically configured depending on whether
the service has selectors defined or not.

- Services with selectors

For headless services that define selectors, the endpoints controller creates
Endpoints records in the API and modifies the DNS configuration to return A
records (addresses) that point directly to the pods backing the service.

- Services without selectors

For headless services that do not define selectors, the endpoints controller
does not create Endpoints records. However, the DNS system looks for and
configures the following records:

- For ExternalName type services, CNAME records.

- For all other service types, A records for any endpoints that share a name
  with the service.
