# Persistent Storage

## Controller-managed Attachment and Detachment benefits

  1. If a node is lost, volumes that were attached to it can be detached by the
     controller and reattached elsewhere.

  2. Credentials for attaching and detaching do not need to be made present on
     every node, improving security.

## Persistent volume snapshots (TECH-PREVIEW)

  1. Create snapshot of a PersistentVolume bound to PersistentVolumeClaim
  2. List existing VolumeSnaphots
  3. Delete existing VolumeSnaphots
  4. Create a new PersistentVolume from an existing VolumeSnaphot
  5. Supported PersistentVolume types:
    a. AWS Elastic Block Store (EBS)
    b. Google Compute Engine (GCE) Persistent Disk (PD)
