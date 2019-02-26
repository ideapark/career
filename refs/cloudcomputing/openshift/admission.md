# Custom Adimission Controllers

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

Some common use-cases include:
 * Mutating resources to inject side-car containers into pods
 * Restricting projects to block some resources from a project
 * Custom resource validation to perform complex validation on dependent fileds
