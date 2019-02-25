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

OKD evaluates authorizations using the following steps:

  1. The identify and the project-scoped action is used to find all bindings that apply to the user or their groups.
  2. Bindings are used to locate all the roles that apply.
  3. Roles are used to find all the rules that apply.
  4. The action is checked against each rule to find a match.
  5. If no matching rule is found, the action is then denied by default.

# ServiceAccount and Secrets

Since every container that runs on the cluster is associated with a service
account, it is also possible to associate secrets to those service accounts and
have them automatically delivered into the container. This enables the
infrastructure to manage secrets for pulling and pushing images, builds, and the
deployment components, and also allows application code to easily leverage those
secrets.
