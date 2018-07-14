# PersistentVolume

Decouple Pod from data volume, Pod does not need to know the specific file
system or persistent engine.

PV: Configure Filesystem or create cloud data volume.
PVC: Associate Pod with PV.

## Volume lifecycle

- Provisioning: staticly created PV, dynamically create by StorageClass.
- Binding: Associate PV with PVC.
- Using: Pod is using this PVC, and can stop PVC from being deleted.
- Releasing: Pod releases Volume and delete PVC.
- Reclaiming: Reclaim PV by deleting or recycling.
- Deleting: Delete PV from cloud storage backend.

## PV accessModes

- ReadWriteOnce (RWO): read and write only by one Pod.
- ReadOnlyMany (ROX): read by multiple Pod.
- ReadWriteMany (RWX): read and write by multiple Pods.
