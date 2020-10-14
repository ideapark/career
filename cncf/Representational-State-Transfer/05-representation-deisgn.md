# Representation Design

## Message Body Format

- JSON should be supported for resource representation
- JSON must be well-formed

```json
{
  "firstName": "Osvaldo",
  "lastName": "Alonso",
  "firstNamePronunciation": "ahs-VAHL-doe",
  "number": 6,
  "birthDate": "1985-11-11"
}
```

- XML and other formats may optionally be used for resource representation
- Additional envelopes must not be created

## Hypermedia Representation

- A consistent form should be used to represent links
- A consistent form should be used to represent link relations
- A consistent form should be used to advertise links
- A self link should be included in response message body representations
- Minimize the number of advertised “entry point” API URIs
- Links should be used to advertise a resource’s available actions in a state-sensitive manner

## Media Type Representation

- A consistent form should be used to represent media type formats
- A consistent form should be used to represent media type schemas

## Error Representation

- A consistent form should be used to represent errors
- A consistent form should be used to represent error responses
- Consistent error types should be used for common error conditions
