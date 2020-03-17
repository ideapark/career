# Custom Resource (CR)

## CR or ConfigMap?

ConfigMaps are best at providing a configuration to a program running in a pod
on the cluster -- think of an application’s config file, like `httpd.conf` or
MySQL’s `mysql.cnf`. Applications usually want to read such configuration from
within their pod, as a file or the value of an environment variable, rather than
from the Kubernetes API.

Kubernetes provides CRs to represent new collections of objects in the API. CRs
are created and accessed by standard Kubernetes clients, like kubectl, and they
obey Kubernetes conventions, like the resources `.spec` and `.status`. At their
most useful, CRs are watched by custom controller code that in turn creates,
updates, or deletes other cluster objects or even arbitrary resources outside of
the cluster.
