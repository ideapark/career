# Authorization

Role-based Access Control (RBAC) objects determine whether a user is allowed to
perform a given action within a project.

It allows developers to use local roles and bindings to control who has access
to their projects. Note that authorization is a separate step from
authentication, which is more about determining the identity of who is taking
the action.

Authorization is managed using:

```text
+----------+--------------------------------------------------------------------------------------------------------------+
| Rules    | Sets of permitted verbs on a set of objects. For example, whether something can create pods.                 |
| Roles    | Collections of rules. Users and groups can be associated with, or bound to, multiple roles at the same time. |
| Bindings | Associations between users and/or groups with a role.                                                        |
+----------+--------------------------------------------------------------------------------------------------------------+
```

The relationships between cluster roles, local roles, cluster role bindings,
local role bindings, users, groups and service accounts are illustrated below.

```text
           Service Account (Bot)            Group 1              User1              User 2             User 3
                    |                          |                   |                  |                  |
                    |                          |                   |                  |                  |
           +-----------------------------------------------------------------------------------+  +-----------------+
           |   LOCAL ROLE                 LOCAL ROLE           LOCAL ROLE         LOCAL ROLE   |  | CLUSTER ROLE    |
           |   BINDING                    BINDING              BINDING            BINDING      |  | BINDING         |
           |                                                                                   |  |                 |
           |   Bot can interact with      Group 1 can view     User 1 can edit    User 2 can   |  | User 3 can      |
           |   specific resource          in project           in project         admin in     |  | cluster admin   |
           |        |                          |                   |              project      |  | in all projects |
           |        |                          |                   |                 |         |  +-----------------+
           |   LOCAL ROLE                      |                   |                 |         |         |
           |   (Bot)                           |                   |                 |         |         |
           |   Rule    Rule                    |                   |                 |         |         |
           |                                   |                   |                 |         |         |
           | PROJECT                           |                   |                 |         |         |
           +-----------------------------------------------------------------------------------+         |
                                               |                   |                 |                   |
                                               |                   |                 |                   |
                                       +---------------------------------------------------------------------------+
                                       | CLUSTER ROLE         CLUSTER ROLE      CLUSTER ROLE        CLUSTER ROLE   |
                                       | (View)               (Edit)            (Admin)             (Cluster Admin |
                                       | Rule  Rule           Rule  Rule        Rule  Rule          Rule  Rule     |
                                       +---------------------------------------------------------------------------+
```
