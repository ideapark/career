# OAuth Objects

## OAuthClient

An OAuthClient represents an OAuth client, the following OAuthClient objects are
automatically created:

| OAuthClient                  | Description                                                                                                 |
| ---                          | ---                                                                                                         |
| openshift-web-console        | Client used to request tokens for the web console.                                                          |
| openshift-browser-client     | Client used to request tokens at /oauth/token/request with a user-agent that can handle interactive logins. |
| openshift-challenging-client | Client used to request tokens with a user-agent that can handle WWW-Authenticate challenges.                |

```yaml
apiVersion: "oauth.openshift.io/v1"
kind: "OAuthClient"
metadata:
  name: "openshift-web-console"
  selflink: "/oapi/v1/oAuthClients/openshift-web-console"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:01Z"
respondWithChallenges: false
accessTokenMaxAgeSeconds: null
secret: "45e27750-a8aa-11e4-b2ea-3c970e4b7ffe"
redirectURIs:
  - "https://localhost:8443"
```

## OAuthClientAuthorization

An OAuthClientAuthorization represents an approval by a User for a particular
OAuthClient to be given an OAuthAccessToken with particular scopes.

Creation of OAuthClientAuthorization objects is done during an authorization
request to the OAuth server.

```yaml
apiVersion: "oauth.openshift.io/v1"
kind: "OAuthClientAuthorization"
metadata:
  name: "bob:openshift-web-console"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:01-00:00"
clientName: "openshift-web-console"
userName: "bob"
userUID: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
scopes: []
```

## OAuthAuthorizeToken

An OAuthAuthorizeToken represents an OAuth authorization code, an
OAuthAuthorizeToken is created by a request to the /oauth/authorize endpoint, an
OAuthAuthorizeToken can then be used to obtain OAuthAccessToken with a request
to the /oauth/token endpoint.

```yaml
apiVersion: "oauth.openshift.io/v1"
kind: "OAuthAuthorizeToken"
metadata:
  name: "MDAwYjM5YjMtMzM1MC00NDY4LTkxODItOTA2OTE2YzE0M2Fj"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:01-00:00"
clientName: "openshift-web-console"
expiresIn: 300
scopes: []
redirectURI: "https://localhost:8443/console/oauth"
userName: "bob"
userUID: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
```

## OAuthAccessToken

An OAuthAccessToken represents an OAuth access token, an OAuthAccessToken is
created by a request to the /oauth/token endpoint. Access token are used as
bearer tokens to authenticate to the API.

```yaml
apiVersion: "oauth.openshift.io/v1"
kind: "OAuthAccessToken"
metadata:
  name: "ODliOGE5ZmMtYzczYi00Nzk1LTg4MGEtNzQyZmUxZmUwY2Vh"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:02-00:00"
clientName: "openshift-web-console"
expiresIn: 86400
scopes: []
redirectURI: "https://localhost:8443/console/oauth"
userName: "bob"
userUID: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
authorizeToken: "MDAwYjM5YjMtMzM1MC00NDY4LTkxODItOTA2OTE2YzE0M2Fj"
```

# User Objects

## Identity

When a user logs into OKD, they do so using a configured identity provider. This
determines the user's identity, and provides that information to OKD. OKD then
looks for a UserIdentityMapping for that Identity.

```yaml
apiVersion: "user.openshift.io/v1"
kind: "Identity"
metadata:
  name: "anypassword:bob"
  uid: "9316ebad-0fde-11e5-97a1-3c970e4b7ffe"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:01-00:00"
providerName: "anypassword"
providerUserName: "bob"
user:
  name: "bob"
  uid: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
```

## User

A User represents an actor in the system. Users are granted permissions by
adding roles to users or to their groups. User objects are created automatically
on first login, or can be created via the API.

```yaml
apiVersion: "user.openshift.io/v1"
kind: "User"
metadata:
  name: "bob"
  uid: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
  resourceVersion: "1"
  creationTimestamp: "2015-01-01T01:01:01-00:00"
identities:
  - "anypassword:bob"
fullName: "Bob User"
```

## UserIdentityMapping

A UserIdentityMapping maps an Identity to a User. Creating, updating, or
deleting a UserIdentityMapping modifies the corresponding fields in the Identity
and User objects. An Identity can only to a single User, so logging in as a
particular identity unambiguously determines the User. A User can have multiple
identities mapped to it. This allows multiple login methods to identify the same
User.

```yaml
apiVersion: "user.openshift.io/v1"
kind: "UserIdentityMapping"
metadata:
  name: "anypassword:bob"
  uid: "9316ebad-0fde-11e5-97a1-3c970e4b7ffe"
  resourceVersion: "1"
identity:
  name: "anypassword:bob"
  uid: "9316ebad-0fde-11e5-97a1-3c970e4b7ffe"
user:
  name: "bob"
  uid: "9311ac33-0fde-11e5-97a1-3c970e4b7ffe"
```

## Group

A Group represents a list of users in the system. Groups are granted permissions
by adding roles to users or to their groups.

```yaml
apiVersion: "user.openshift.io/v1"
kind: "Group"
metadata:
  name: "developers"
  creationTimestamp: "2015-01-01T01:01:01-00:00"
users:
  - "bob"
```
