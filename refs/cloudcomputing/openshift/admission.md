# Adimission Controller

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
