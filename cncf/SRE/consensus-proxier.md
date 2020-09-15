# Use proxier to reduce TCP/IP connections between client and consensus server

```text
+-------------------------+                                  +----------------------+
|Region                   |                                  | Region               |
|  +-------------------+  |  Persistent TCP/IP connections   | +------------------+ |
|  | Consensus Cluster |--|----------------------------------|-| Regional Proxies | |
|  |        ##         |  |                                  | +------------------+ |
|  |        ##         |  |                                  |    /     |      \<---|------ Ephemeral TCP/IP connections
|  |       /  \        |  |                                  | Client Client Client |
|  |     ## -- ##      |  |                                  +----------------------+
|  |     ##    ##      |  |
|  +-------------------+  |
+------------------|------+
                   | Persistent TCP/IP connections
               +---|------------------+
               |   |          Region  |
               | +------------------+ |
               | | Regional Proxies | |
               | +------------------+ |
               |    /     |      |<---|------ Ephemeral TCP/IP connections
               | Client Client Client |
               +----------------------+
```
