# Modifying an existing resource in Kubernetes

- kubectl edit

Opens the objects's manifest in your default editor. After making changes,
saving the file, and exiting the editor, the object is updated.

- kubectl patch

Modifies individual properties of an object.

- kubectl apply

Modifies the object by applying property values from a full YAML or JSON file.
If the object specified in the YAML/JSON doesn't exist yet, it's created. The
file needs to contain the full definition of the resource (it can't include only
the fields you want to update, as is the case with kubectl patch).

- kubectl replace

Replaces the object with a new one from a YAML/JSON file. In contrast to the
apply command, this command requires the object to exist; otherwise it prints an
error.

- kubectl set image

Changes the container image defined in a Pod, ReplicationController's template,
Deployment, DaemonSet, Job, a ReplicaSet.
