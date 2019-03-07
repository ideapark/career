# Stateful vs. Stateless

```text
                                             STATEFUL
                                                 ^
                                                 |
                                counter          |                  financial transaction
                                                 |
                     shopping basket             |         user management
    no disk I/O <---------------------- read-only disk I/O -------------------------------> read-write disk I/O
                                                 |
                                                 |
                        geo coordinates          |         file upload
                                                 |
                                            web server
                                                 |
                                                 v
                                             STATELESS
```
