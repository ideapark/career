# Go Modules

```text
                                           +-------------------------------+                                 +----------------+
                            +------------->| download/github.com/me/.ib/@v |-------------------------------->|        list    |
+-------------------------+/               +-------------------------------+                                 +----------------+
|          cache          |--------------->|            vcs/<hash>         |---------+                       | v1.0.0.info    |
+-------------------------+                +-------------------------------+          \                      +----------------+
| github.com/me/lib@1.0.0 |------+                                                     \                     | v1.0.0.mod     |
+-------------------------+       \                                                     \                    +----------------+
                                   \ +-----------+                                       v                   | v1.0.0.zip     |
                                    >| go.mod    |                                        +--------------+   +----------------+
                                     +-----------+                                        | <hash>[.git] |   | v1.0.0.ziphash |
                                     | lib.go    |                                        +--------------+   +----------------+
                                     +-----------+                                        | <hash>.info  |
                                     | README.md |                                        +--------------+
                                     +-----------+
```

- Dependencies source trees are placed at the root of this directory, with a slight change: the import path is suffixed with @version
- Source archives retrieved or built from VCS are stored in the download folder
- VCS data is stored in the *vcs* folder
