# Cluster Roles and Local Roles

Roles are collections or policy rules, which are sets of permitted verbs that
can be performed on a set of resources. OKD includes a set of default cluster
roles that can be bound to users and groups cluster wide or locally.

| Default Cluster Roles | Description                                                                                                                                                                              |
| ---                   | ---                                                                                                                                                                                      |
| admin                 | A project manager. If used in a local binding, an admin user will have rights to view and modify any resource in the project except for quota.                                           |
| basic-user            | A user that can get basic information about project except for quota.                                                                                                                    |
| cluster-admin         | A super-user that can perform any action in any project. When bound to a user with a local binding, they have full control over quota and every action on every resource in the project. |
| cluster-status        | A user that can get basic cluster status information.                                                                                                                                    |
| edit                  | A user that can modify most objects in a project, but does not have the power to view or modify roles or bindings.                                                                       |
| self-provisioner      | A user that can create their own projects.                                                                                                                                               |
| view                  | A user who cannot make any modifications, but can see most objects in a project. They cannot view or modify roles or bindings.                                                           |
| cluster-reader        | A user who can read, but not view, objects in the cluster.                                                                                                                               |
