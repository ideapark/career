# Custom Adimission Controllers

```text
               +---------+         +----------------+        +-----------+       +------------+        +------------+        +-----------+
               |   API   |         |                |        |           |       |            |        |            |        |           |
 API request   |  HTTP   |         | Authentication |        | Mutating  |       |   Object   |        | Validating |        | Persisted |
-------------> | handler | ------> |  Authorization | -----> | admission | ----> |  Schema    | -----> | admission  | -----> |  to etcd  |
               |         |         |                |        |           |       | Validation |        |            |        |           |
               +---------+         +----------------+        +-----------+       +------------+        +------------+        +-----------+
                                                               ^       ^                                    ^   |
                                                               |       |                                    |   |
                                                               |       |                                    |   V
                                                      +---------+     +---------+                            +---------+
                                                      | Webhook |     | Webhook |                          +---------+ |
                                                      +---------+     +---------+                        +---------+ | +
                                                                                                         | Webhook | +
                                                                                                         +---------+
```

Some common use-cases include:
 * Mutating resources to inject side-car containers into pods
 * Restricting projects to block some resources from a project
 * Custom resource validation to perform complex validation on dependent fileds

# Admission Controllers

- AlwaysAdmit

This admission controller allows all pods into the cluster. It is deprecated
because its behavior is the same as if there were no admission controller at
all.

- AlwaysPullImages

This admission controller modifies every new Pod to force the image pull policy
to Always. This is useful in a multitenant cluster so that users can be assured
that their private images can only be used by those who have the credentials to
pull them. Without this admission controller, once an image has been pulled to a
node, any pod from any user can use it simply by knowing the image’s name
(assuming the Pod is scheduled onto the right node), without any authorization
check against the image. When this admission controller is enabled, images are
always pulled prior to starting containers, which means valid credentials are
required.

- AlwaysDeny

Rejects all requests. AlwaysDeny is DEPRECATED as no real meaning.

- DefaultStorageClass

This admission controller observes creation of PersistentVolumeClaim objects
that do not request any specific storage class and automatically adds a default
storage class to them. This way, users that do not request any special storage
class do not need to care about them at all and they will get the default one.

This admission controller does not do anything when no default storage class is
configured. When more than one storage class is marked as default, it rejects
any creation of PersistentVolumeClaim with an error and an administrator must
revisit their StorageClass objects and mark only one as default. This admission
controller ignores any PersistentVolumeClaim updates; it acts only on creation.

See persistent volume documentation about persistent volume claims and storage
classes and how to mark a storage class as default.

- DefaultTolerationSeconds

This admission controller sets the default forgiveness toleration for pods to
tolerate the taints notready:NoExecute and unreachable:NoExecute for 5 minutes,
if the pods don’t already have toleration for taints
*node.kubernetes.io/not-ready:NoExecute* or
*node.alpha.kubernetes.io/unreachable:NoExecute*.

- DenyExecOnPrivileged

This admission controller will intercept all requests to exec a command in a pod
if that pod has a privileged container.

This functionality has been merged into DenyEscalatingExec. The
DenyExecOnPrivileged admission plugin is deprecated and will be removed in
v1.18.

Use of a policy-based admission plugin (like PodSecurityPolicy or a custom
admission plugin) which can be targeted at specific users or Namespaces and also
protects against creation of overly privileged Pods is recommended instead.

- DenyEscalatingExec

This admission controller will deny exec and attach commands to pods that run
with escalated privileges that allow host access. This includes pods that run as
privileged, have access to the host IPC namespace, and have access to the host
PID namespace.

The DenyEscalatingExec admission plugin is deprecated and will be removed in
v1.18.

Use of a policy-based admission plugin (like PodSecurityPolicy or a custom
admission plugin) which can be targeted at specific users or Namespaces and also
protects against creation of overly privileged Pods is recommended instead.

- EventRateLimit

This admission controller mitigates the problem where the API server gets
flooded by event requests.

- ExtendedResourceToleration

This plug-in facilitates creation of dedicated nodes with extended resources. If
operators want to create dedicated nodes with extended resources (like GPUs,
FPGAs etc.), they are expected to taint the node with the extended resource name
as the key. This admission controller, if enabled, automatically adds
tolerations for such taints to pods requesting extended resources, so users
don’t have to manually add these tolerations.

- ImagePolicyWebhook

he ImagePolicyWebhook admission controller allows a backend webhook to make
admission decisions.

- Initializers

The admission controller determines the initializers of a resource based on the
existing InitializerConfigurations. It sets the pending initializers by
modifying the metadata of the resource to be created. For more information,
please check Dynamic Admission Control.

- LimitPodHardAntiAffinityTopology

This admission controller denies any pod that defines AntiAffinity topology key
other than *kubernetes.io/hostname* in
*requiredDuringSchedulingRequiredDuringExecution*.

- LimitRanger

This admission controller will observe the incoming request and ensure that it
does not violate any of the constraints enumerated in the LimitRange object in a
Namespace. If you are using LimitRange objects in your Kubernetes deployment,
you MUST use this admission controller to enforce those constraints. LimitRanger
can also be used to apply default resource requests to Pods that don’t specify
any; currently, the default LimitRanger applies a 0.1 CPU requirement to all
Pods in the default namespace.

See the limitRange design doc and the example of Limit Range for more details.

- MutatingAdmissionWebhook

This admission controller calls any mutating webhooks which match the request.
Matching webhooks are called in serial; each one may modify the object if it
desires.

This admission controller (as implied by the name) only runs in the mutating
phase.

If a webhook called by this has side effects (for example, decrementing quota)
it must have a reconciliation system, as it is not guaranteed that subsequent
webhooks or validating admission controllers will permit the request to finish.

- NamespaceAutoProvision

This admission controller examines all incoming requests on namespaced resources
and checks if the referenced namespace does exist. It creates a namespace if it
cannot be found. This admission controller is useful in deployments that do not
want to restrict creation of a namespace prior to its usage.

- NamespaceExists

This admission controller checks all requests on namespaced resources other than
Namespace itself. If the namespace referenced from a request doesn’t exist, the
request is rejected.

- NamespaceLifecycle

This admission controller enforces that a Namespace that is undergoing
termination cannot have new objects created in it, and ensures that requests in
a non-existent Namespace are rejected. This admission controller also prevents
deletion of three system reserved namespaces *default*, *kube-system*,
*kube-public*.

A Namespace deletion kicks off a sequence of operations that remove all objects
(pods, services, etc.) in that namespace. In order to enforce integrity of that
process, we strongly recommend running this admission controller.

- NodeRestriction

This admission controller limits the Node and Pod objects a kubelet can modify.
In order to be limited by this admission controller, kubelets must use
credentials in the *system:nodes* group, with a username in the form
*system:node:<nodeName>*. Such kubelets will only be allowed to modify their own
Node API object, and only modify Pod API objects that are bound to their node.
In Kubernetes 1.11+, kubelets are not allowed to update or remove taints from
their Node API object.

- OwnerReferencesPermissionEnforcement

This admission controller protects the access to the metadata.ownerReferences of
an object so that only users with “delete” permission to the object can change
it. This admission controller also protects the access to
metadata.ownerReferences[x].blockOwnerDeletion of an object, so that only users
with “update” permission to the finalizers subresource of the referenced owner
can change it.

- PersistentVolumeLabel

This admission controller automatically attaches region or zone labels to
PersistentVolumes as defined by the cloud provider (for example, GCE or AWS). It
helps ensure the Pods and the PersistentVolumes mounted are in the same region
and/or zone. If the admission controller doesn’t support automatic labelling
your PersistentVolumes, you may need to add the labels manually to prevent pods
from mounting volumes from a different zone. PersistentVolumeLabel is DEPRECATED
and labeling persistent volumes has been taken over by cloud controller manager.
Starting from 1.11, this admission controller is disabled by default.

- PodNodeSelector

This admission controller defaults and limits what node selectors may be used
within a namespace by reading a namespace annotation and a global configuration.

- PersistentVolumeClaimResize

This admission controller implements additional validations for checking
incoming PersistentVolumeClaim resize requests.

- PodPreset

This admission controller injects a pod with the fields specified in a matching
PodPreset. See also PodPreset concept and Inject Information into Pods Using a
PodPreset for more information.

- PodSecurityPolicy

This admission controller acts on creation and modification of the pod and
determines if it should be admitted based on the requested security context and
the available Pod Security Policies.

- PodTolerationRestriction

This admission controller first verifies any conflict between a pod’s
tolerations and its namespace’s tolerations, and rejects the pod request if
there is a conflict. It then merges the namespace’s tolerations into the pod’s
tolerations. The resulting tolerations are checked against the namespace’s
whitelist of tolerations. If the check succeeds, the pod request is admitted
otherwise rejected.

- Priority

The priority admission controller uses the priorityClassName field and populates
the integer value of the priority. If the priority class is not found, the Pod
is rejected.

- ResourceQuota

This admission controller will observe the incoming request and ensure that it
does not violate any of the constraints enumerated in the ResourceQuota object
in a Namespace. If you are using ResourceQuota objects in your Kubernetes
deployment, you MUST use this admission controller to enforce quota constraints.

See the resourceQuota design doc and the example of Resource Quota for more
details.

- SecurityContextDeny

This admission controller will deny any pod that attempts to set certain
escalating SecurityContext fields. This should be enabled if a cluster doesn’t
utilize pod security policies to restrict the set of values a security context
can take.

- ServiceAccount

This admission controller implements automation for serviceAccounts. We strongly
recommend using this admission controller if you intend to make use of
Kubernetes ServiceAccount objects.

- StorageObjectInUseProtection

The *StorageObjectInUseProtection* plugin adds the
*kubernetes.io/pvc-protection* or kubernetes.io/pv-protection finalizers to
newly created Persistent Volume Claims (PVCs) or Persistent Volumes (PV). In
case a user deletes a PVC or PV the PVC or PV is not removed until the finalizer
is removed from the PVC or PV by PVC or PV Protection Controller. Refer to the
Storage Object in Use Protection for more detailed information.

- ValidatingAdmissionWebhook

This admission controller calls any validating webhooks which match the request.
Matching webhooks are called in parallel; if any of them rejects the request,
the request fails. This admission controller only runs in the validation phase;
the webhooks it calls may not mutate the object, as opposed to the webhooks
called by the MutatingAdmissionWebhook admission controller.

# Recommended set of admission controller to use

- Kubernetes version 1.10 and later

```bash
--enable-admission-plugins=NamespaceLifecycle,\
                           LimitRanger,\
                           ServiceAccount,\
                           DefaultStorageClass,\
                           DefaultTolerationSeconds,\
                           MutatingAdmissionWebhook,\
                           ValidatingAdmissionWebhook,\
                           Priority,\
                           ResourceQuota
```

- Kubernetes version 1.9 and eaarlier

```bash
--admission-control=NamespaceLifecycle,\
                    LimitRanger,\
                    ServiceAccount,\
                    DefaultStorageClass,\
                    DefaultTolerationSeconds,\
                    MutatingAdmissionWebhook,\
                    ValidatingAdmissionWebhook,\
                    ResourceQuota
```
