# Container Storage Interface

- external-attacher

Watches Kubernetes VolumeAttachment objects and triggers ControllerPublish and
ControllerUnpublish operations against a CSI endpoint.

- external-provisioner

Watches Kubernetes PersistenVolumeClaim objects and triggers CreateVolume and
DeleteVolume operations against a CSI endpoint.

- node-driver-registar

Registers the CSI driver with kubelet using the Kubelet device plugin mechanism.

- cluster-driver-registar (Alpha)

Registers a CSI Driver with the Kubernetes cluster by creating a CSIDriver
object which enabls the driver to customize how Kubernetes interacts with it.

- external-snapshotter (Alpha)

Watches Kubernetes VolumeSnapshot CRD objects and triggers CreateSnapshot and
DeleteSnapshot operations agains a CSI endpoint.

- livenessprobe

May be included in a CSI plugin pod to enable the Kubernetes Liveness Probe
mechanism.
