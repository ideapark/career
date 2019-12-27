# REST API

## Authentication

API calls must be authenticated with an *access token* or *X.509 certificate*.
With token authentication, a bearer token must be passed in as an HTTP
Authorization header. There are two types of access tokens: session and service
account.

- Session Tokens

A session token is short-lived, expiring within 24 hours by default. It
represents a user. After logging in, the session token may be obtained with the
*oc whoami* command.

```bash
$ oc whoami
developer
$ oc whoami -t
BucUosuzMOkUZHHGUsTb98OOQPudFvP0uHsqNE94cTs
```

- Service Account Tokens

Service account tokens are long-lived tokens. They are JSON Web Token (JWT)
formatted tokens and are much longer strings than session tokens.

```bash
$ oc serviceaccounts get-token default
eyJhbGciOiJSUzI1NiIsImtpZCI6IiJ9.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJnbnUiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlY3JldC5uYW1lIjoiZGVmYXVsdC10b2tlbi16Z3AycyIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50Lm5hbWUiOiJkZWZhdWx0Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiOWJjMjJmYzEtNGVjMC0xMWU5LTgwNDgtMTIyNjMxNjMyZjQyIiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50OmdudTpkZWZhdWx0In0.V0I0pkQAfioJXsvnTi8NXUedoY_gOUyzX5T811B1Roa5hO5KmBYZnxbD0fImEaHvJ5MNXM9F_d7CVq7JUUXsFS54RFeN4ChdfW4dyNruKGR6W1Y4jkAw6A0n8aAAFb5bgzCgg2_x7W4KYEtCEZ9IE_lDNqAef84jba8ZC7BWuNGYXjzAVzAqq4EhO_EJn1y33qhzTre2ksyOKrQWHSnxnFjJb0hrrzxNsALJYYUJvSxzGRx1InLMdM_acuLSHWWwgIgN7S2gvdMmch5Tcj23rFjCyP9UlB3HbWgebexrX5ATH48LPe06D1ointkeslZ8uazFgODG4W0uiXksxcGMdg
```
