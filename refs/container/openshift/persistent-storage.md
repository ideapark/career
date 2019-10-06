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

## Storage options

### Block

- Description
  1. Presented to the operating system (OS) as a block device
  2. Suitable for applications that need full controll of storage and operate at a low level on files bypassing the file system
  3. Also referred to as a Storage Area Network (SAN)
  4. Non-shareable, which means that only one client at a time can mount an endpoint of this type

- Examples
  1. Containerized GlusterFS/External GlusterFS GlusterFS iSCSI
  2. Fibre Channel
  3. Ceph RBD
  4. OpenStack Cinder
  5. AWS EBS
  6. Dell/EMC Scale.IO
  7. VMware vSphere Volume
  8. GCE Persistent Disk
  9. Azure Disk

### File

- Description
  1. Presented to the OS as a file system export to be mounted
  2. Also referred to as Network Attached Storage (NAS)
  3. Concurrency, latency, file locking mechanisms, and other capabilities vary widely between protocols, implementations, vendors, and scales.

- Examples
  1. Containerized GlusterFS/External GlusterFS GlusterFS
  2. RHEL NFS
  3. NetApp NFS
  4. Azure File
  5. Vendor NFS
  6. Vendor GlusterFS
  7. Azure File
  8. AWS EFS

### Object

- Description
  1. Accessible through a REST API endpoint
  2. Configurable for use in the OKD Registry
  3. Applications must build their drivers into the application and/or container

- Examples
  1. Containerized GlusterFS/External GlusterFS GlusterFS
  2. Ceph Object Storage (RADOS Gateway)
  3. OpenStack Swift
  4. Aliyun OSS
  5. AWS S3
  6. Google Cloud Storage
  7. Azure Blob Storage
  8. Vendor S3
  9. Vendor Swift

## Storage howto

| Storage type | ROX | RWX | Registry     | Scaled registry[1] | Metrics          | Logging          | Apps             |
| ---          | --- | --- | ---          | ---                | ---              | ---              | ---              |
| Block        | Yes | No  | Configurable | Not configurable   | Recommended      | Recommended      | Recommended      |
| File         | Yes | Yes | Configurable | Configurable       | Configurable     | Configurable     | Recommended      |
| Object       | Yes | Yes | Recommended  | Recommended        | Not configurable | Not configurable | Not Configurable |

[1]: A scaled registry is an OKD registry where three or more pod replicas are running.
