# Secrets

The value in the type field indicates the structure of the secret’s key names
and values. The type can be used to enforce the presence of user names and keys
in the secret object. If you do not want validation, use the opaque type, which
is the default.

Specify one of the following types to trigger minimal server-side validation to
ensure the presence of specific key names in the secret data:

| TYPE                                | DESCRIPTION                                                     |
| ---                                 | ---                                                             |
| kubernetes.io/service-account-token | Uses a service account token                                    |
| kubernetes.io/dockercfg             | Uses a .dockercfg file for required Docker credentials          |
| kubernetes.io/dockerconfigjson      | Uses a .docker/config.json file for required Docker credentials |
| kubernetes.io/basic-auth            | Use with Basic Authentication                                   |
| kubernetes.io/ssh-auth              | Use with SSH Key Authentication                                 |
| kubernetes.io/tls                   | Use with TLS certificate authorities                            |

Specify type= Opaque if you do not want validation, which means the secret does
not claim to conform to any convention for key names or values. An opaque
secret, allows for unstructured key:value pairs that can contain arbitrary
values.
