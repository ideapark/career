# Metadata Design

## HTTP Headers

- Content-Type must be used
- Content-Length should be used
- Last-Modified should be used in responses
- ETag should be used in responses
- Stores must support conditional PUT requests
- Location must be used to specify the URI of a newly created resource
- Cache-Control, Expires, and Date response headers should be used to encourage caching

```text
Cache-Control: max-age=60, must-revalidate
Date: Tue, 15 Nov 1994 08:12:31 GMT
Expires: Thu, 01 Dec 1994 16:00:00 GMT
```

- Cache-Control, Expires, and Pragma response headers may be used to discourage caching
- Caching should be encouraged
- Expiration caching headers should be used with 200 (“OK”) responses
- Expiration caching headers may optionally be used with 3xx and 4xx responses
- Custom HTTP headers must not be used to change the behavior of HTTP methods

## Media Types

> type "/" subtype *( ";" parameter )

```text
Content-type: text/html; charset=ISO-8859-4
Content-type: text/plain; charset="us-ascii"

text/plain               A plain text format with no specific content structure or markup.
text/html                Content that is formatted using the HyperText Markup Language (HTML).
image/jpeg               An image compression method that was standardized by the Joint Photographic Experts Group (JPEG).
application/xml          Content that is structured using the Extensible Markup Language (XML).
application/atom+xml     Content that uses the Atom Syndication Format (Atom), which is an XML-based format that structures data into lists known as feeds.
application/javascript   Source code written in the JavaScript programming language.
application/json         The JavaScript Object Notation (JSON) text-based format that is often used by programs to exchange structured data.
```

## Media Type Design

- Application-specific media types should be used
- Media type negotiation should be supported when multiple representations are available
- Media type selection using a query parameter may be supported
