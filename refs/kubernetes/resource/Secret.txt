# Secret

Secret stands for password, token, private configuration data, used as Volume or
environment variables.

# Secret vs ConfigMap

- similarity

1) key/value
2) export to environment
3) namespace specific
4) mounted as directory/file

- difference

1) Secret can associate with ServerAccount
2) Secret can store docker register authentication information, used to pull private image
3) Secret support Base64 encoded
4) Secret consists of Opaque, kubernetes.io/ServiceAccount, kubernetes.io/dockerconfigjson
5) Secret stored in tmpfs filesystem, Secret files will be deleted when Pod deleted
