# Interaction Design with HTTP

## Request Methods

> Request-Line = Method SP Request-URI SP HTTP-Version CRLF

- GET and POST must not be used to tunnel other request methods

- GET must be used to retrieve a representation of a resource

```text
  $ curl -v http://api.example.restapi.org/greeting

  > GET /greeting HTTP/1.1
  > User-Agent: curl/7.20.1
  > Host: api.example.restapi.org
  > Accept: */*

  < HTTP/1.1 200 OK
  < Date: Sat, 20 Aug 2011 16:02:40 GMT
  < Server: Apache
  < Expires: Sat, 20 Aug 2011 16:03:40 GMT
  < Cache-Control: max-age=60, must-revalidate
  < ETag: text/html:hello world
  < Content-Length: 130
  < Last-Modified: Sat, 20 Aug 2011 16:02:17 GMT
  < Vary: Accept-Encoding
  < Content-Type: text/html

  <!doctype html><head><meta charset="utf-8"><title>Greeting</title></head> <body><div id="greeting">Hello World!</div></body></html>
```

- HEAD should be used to retrieve response headers

```text
  $ curl --head http://api.example.restapi.org/greeting

  HTTP/1.1 200 OK
  Date: Sat, 20 Aug 2011 16:02:40 GMT
  Server: Apache
  Expires: Sat, 20 Aug 2011 16:03:40 GMT
  Cache-Control: max-age=60, must-revalidate
  ETag: text/html:hello world
  Content-Length: 130
  Last-Modified: Sat, 20 Aug 2011 16:02:17 GMT
  Vary: Accept-Encoding
  Content-Type: text/html
```

- PUT must be used to both insert and update a stored resource

> PUT /accounts/4ef2d5d0-cb7e-11e0-9572-0800200c9a66/buckets/objects/4321

- PUT must be used to update mutable resources

- POST must be used to create a new resource in a collection

> POST /leagues/seattle/teams/trebuchet/players

- POST must be used to execute controllers

> POST /alerts/245743/resend

- DELETE must be used to remove a resource from its parent

> DELETE /accounts/4ef2d5d0-cb7e-11e0-9572-0800200c9a66/buckets/objects/4321

- OPTIONS should be used to retrieve metadata that describes a resource’s available interactions

> Allow: GET, PUT, DELETE

## Response Status Codes

> Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF

```text
  1xx: Informational     Communicates transfer protocol-level information.
  2xx: Success           Indicates that the client’s request was accepted successfully.
  3xx: Redirection       Indicates that the client must take some additional action in order to complete their request.
  4xx: Client Error      This category of error status codes points the finger at clients.
  5xx: Server Error      The server takes responsibility for these error status codes.
```

- 200 (“OK”) should be used to indicate nonspecific success
- 200 (“OK”) must not be used to communicate errors in the response body
- 201 (“Created”) must be used to indicate successful resource creation
- 202 (“Accepted”) must be used to indicate successful start of an asynchronous action
- 204 (“No Content”) should be used when the response body is intentionally empty
- 301 (“Moved Permanently”) should be used to relocate resources
- 302 (“Found”) should not be used
- 303 (“See Other”) should be used to refer the client to a different URI
- 304 (“Not Modified”) should be used to preserve bandwidth
- 307 (“Temporary Redirect”) should be used to tell clients to resubmit the request to another URI
- 400 (“Bad Request”) may be used to indicate nonspecific failure
- 401 (“Unauthorized”) must be used when there is a problem with the client’s credentials
- 403 (“Forbidden”) should be used to forbid access regardless of authorization state
- 404 (“Not Found”) must be used when a client’s URI cannot be mapped to a resource
- 405 (“Method Not Allowed”) must be used when the HTTP method is not supported
- 406 (“Not Acceptable”) must be used when the requested media type cannot be served
- 409 (“Conflict”) should be used to indicate a violation of resource state
- 412 (“Precondition Failed”) should be used to support conditional operations
- 415 (“Unsupported Media Type”) must be used when the media type of a request’s payload cannot be processed
- 500 (“Internal Server Error”) should be used to indicate API malfunction
