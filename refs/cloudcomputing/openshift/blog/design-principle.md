# Application Design Principles to Cope with OpenShift Maintenance Operations

- Always run at least 2 Pods

This is an obvious HA principle, but it has some less obvious ramifications. We
know that our pods will be killed, so we need to have more than one running.
This means that the application needs to be designed to operate with more than
one instance.

- Spread your application Pods evenly across nodes

We do not want to have all our pods on the same node, because that would make
having multiple pods irrelevant when the node must be taken offline.

OpenShift does a good job already at this. The scheduler by default will try to
spread your pods across all the nodes that can house them. The general
recommendation here is to not interfere with OpenShift’s normal scheduling
policy.

- Define a Pod disruption budget

Even with the above techniques in place, there is still a chance that multiple
pods of your app will land on the same node. Also, an administrator may decide
to take multiple nodes offline which may correspond to the nodes the application
is running on. We can inform OpenShift of how many pods an app can tolerate
being down without affecting its normal execution through the
PodDisruptionBidget object.

- Define a descheduler policy

Even with all the above techniques accounted for, once a maintenance event has
been completed, pods may be scheduled in an unbalanced manner. To be better
prepared for the next maintenance event, we may have to make sure pods are
scheduled evenly.

- Do not use local/host path storage

In order to let your pods move around freely, your application should not use
local or hostPath volumes. In fact, local storage will tie pods to the node
where the storage exists, making it impossible for the pod to migrate. So during
a maintenance operation, those pods will simply not be available.

- Design your application so that it tolerate losing Pods

The way OpenShift kills pods is by sending a SIGTERM signal to the app. At this
point the app has some time to shutdown. If the pod does not die within a given
amount of time, the OpenShift will send a SIGKILL to the app process,
terminating it instantly.

You need to instrument your app to do any necessary clean up when it receives a
SIGTERM. This phase has to be quick.

In the case of a web app, there is no time at this point to wait for existing
client sessions to be concluded. This leads us to the next principle.

- It shouldn't matter which Pod receives a request

Because there is no way to clean in-flight sessions when a pod gets killed, it
may happen that subsequent requests of an inflight session go to a different
pod, after the pod that was managing that session is killed.

Your application needs to be designed around this eventuality. It might be ok to
lose the session in some cases. But in most circumstances, you will want to give
your customer the best user experience, which means not losing the session.

If your server-side application is completely stateless, then you have no issues
to worry about. If your server-side application maintains a state in the form of
a session, then you need a way to persist it to either a cache or a database, so
that it can be retrieved by other pods.

- Capacity considerations

Doing maintenance requires having some spare capacity. At a minimum, one needs
to be able to take one node off the cluster. Performing cluster maintenance on
one node at a time can take a long time for large cluster. One can obviously
take multiple nodes offline, but that requires having more spare capacity. Find
the right balance between the spare capacity reserved for maintenance, and the
time the maintenance operation will take.
