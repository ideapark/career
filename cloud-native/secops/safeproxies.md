# Safe Proxies

- Zero Touch Prod

```text
                  +-----------+
                  | Approvers |
                  +-----------+
                        ^
                        .
                        .
                        v
                +------------------+
                | Approval Service |
                +------------------+
                        ^
      +------+          .                           / Read resource
      | User | \        .                          /
      +------+  \       v                         /
                 \  +-------+                    /
                  > | Proxy |-------------------|---- Write resource
                 /  +-------+                    \
+------------+  /       .                         \
| Automation | /        .                          \
+------------+          .                           \ Modify resource
                        v
               +-----------------+
               | Logging Service |
               +-----------------+

    CLIENT                                       TARGET SYSTEM APPLICATIONS
```

- Policy

```json
config = {
  proxy_role = 'admin-proxy'
  tools = {
    borg = {
      mpm = 'client@live'
      binary_in_mpm = 'borg'
      any_command = true
      allow = ['group:admin']
      require_mpa_approval_from = ['group:admin-leads']
      unit_tests = [{
        expected = 'ALLOW'
        command = 'file.borgcfg up'
      }]
    }
  }
}
```
