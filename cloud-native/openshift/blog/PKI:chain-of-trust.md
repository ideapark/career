# PKI

The roles of root certificate, intermediate certificate and end-entity
certificate as in the chain of trust.

```text
End-entity Certificate
+----------------------+
| Owner's name         |
+----------------------+
| Owner's public key   |
+----------------------+      reference
| Issuer's (CA's) name |---------------------+
+----------------------+                     |
| Issuer's signature   |                     v  Intermediate Certificate
+----------------------+              +---------------------------+
            ^                         | Owner's (CA's) name       |
            |          sign           +---------------------------+
            +-------------------------| Owner's public key        |
                                      +---------------------------+      reference
                                      | Issuer's (root CA's) name |---------------------+
                                      +---------------------------+                     |
                                      | Issuer's signature        |                     v
                                      +---------------------------+             +----------------------+
                                                        ^                       | Root CA's name       |
                                                        |         sign          +----------------------+
                                                        +-----------------------| Root CA's public key |
                                                                       +--------|----------------------+
                                                                       +------->| Root CA's signagure  |
                                                                     self-sign  +----------------------+
                                                                                     Root Certificate
```
