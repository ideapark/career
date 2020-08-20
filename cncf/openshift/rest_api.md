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
eyJhbGciOiJSUzI1NiIsImtpZCI6IjZvWFNVWEg2T3ZZWXhyaDVWbFpzSU5jVnYzZkVrbmZ1aFdSeGxaWURKLUEifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJkZWZhdWx0Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZWNyZXQubmFtZSI6ImRlZmF1bHQtdG9rZW4tdnpxcmQiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoiZGVmYXVsdCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50LnVpZCI6IjUyODk5NzNhLWMwMzgtNDFhZC1iNTQzLWY5ODQ1YmU4MzE1YSIsInN1YiI6InN5c3RlbTpzZXJ2aWNlYWNjb3VudDpkZWZhdWx0OmRlZmF1bHQifQ.qGeYo-5GqE5_cnkutGT9kWt0hWJPAyrfAy2DGAHBDskKruVRMxJY38D5fEm5cU_eu_-lo64FuLXV6wmZt9WSb8AvWil5SB3Ys8SA3Tlf8scJBZZcxVs1MwoIs4qN0M-FS9BcW_ReZkrUqr_sKLUBI2TYMKOvlYSbY87VwS-JV1E3M14gAPozuLx1cVKJ9EZvORd9_dwvRYjWYWJbWE_6o1Lddmh50cYAc3sopxjyHp3pb8GcSQFoPHIkZKnCwm1_vkqu1RLiF2UWYLVXCjLv1f0BqnQmo1e0L8y-n5xaZgAEod6XC0UkWqWQSPSr-sG6B4UpNwCtM8M5SUHOm3318g
```

- https://jwt.io

```json
{
  "alg": "RS256",
  "kid": "6oXSUXH6OvYYxrh5VlZsINcVv3fEknfuhWRxlZYDJ-A"
}
{
  "iss": "kubernetes/serviceaccount",
  "sub": "system:serviceaccount:default:default"
  "kubernetes.io/serviceaccount/namespace": "default",
  "kubernetes.io/serviceaccount/secret.name": "default-token-vzqrd",
  "kubernetes.io/serviceaccount/service-account.name": "default",
  "kubernetes.io/serviceaccount/service-account.uid": "5289973a-c038-41ad-b543-f9845be8315a",
}
```
