# Client Concerns

## Versioning

- New URIs should be used to introduce new concepts
- Schemas should be used to manage representational form versions
- Entity tags should be used to manage representational state versions

## Security

- OAuth may be used to protect resources
- API management solutions may be used to protect resources

## Response Representation Composition

- The query component of a URI should be used to support partial responses
- The query component of a URI should be used to embed linked resources

## Processing Hypermedia

### JavaScript Clients

- JSONP should be supported to provide multi-origin read access from JavaScript
- CORS should be supported to provide multi-origin read/write access from JavaScript
