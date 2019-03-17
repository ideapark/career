# Persistent Storage

## Controller-managed Attachment and Detachment benefits

  1. If a node is lost, volumes that were attached to it can be detached by the
     controller and reattached elsewhere.

  2. Credentials for attaching and detaching do not need to be made present on
     every node, improving security.
