# OAuth

OAuth is an HTTP-based authorization protocol that enables the protection of
resources. The OAuth protocol's flow is summarized in the steps below:

- A client obtains the artifacts needed to interact with a REST API's protected
  resources. Note that with respect to the character of these artifacts and how
  they are obtained, there are some significant diferences between versions of
  the OAuth protocol specification.

- Using the artifacts that it obtained in Step 1, the client requests an
  interaction with a REST API's protected resource.

- The REST API, or an intermediary acting on its behalf, validates the client
  request's OAuth-based authorization information. Note that there are some
  significant differences in the validation process as detailed by the OAuth 1.0
  and 2.0 specifications.

- If the validation check succeeds, the REST API allows the client's interaction
  with the protected resource to proceed.
