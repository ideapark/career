# Four Hosted Registries Comparison

## Concepts

- Index

An index tracks namespaces and docker repositories. For example, Docker Hub is a
centralized index for public repositories.

- Registry

A docker registry is responsible for storing images and repository graphs. A
registry typically hosts multiple docker repositories.

- Repository

A docker repository is a logical collection of tags for an individual docker
image, and is quite similar to a git repository. Like the git conterpart, a
docker repository is identified by a URI and can either be public or private.
The URI looks like:

```text
{registry_address}/{namespace}/{repository_name}:{tag}

quay.io/library/golang:alpine
```

## Evaluate Hosted Registries

### Criteria

- Workflow (build/deployment, collaboration, ease of use and visibility)
- Authentication and authorization
- Availability and performance
- Pricing

### Comparison Table

| Criteria    | Docker Hub                     | Quay.io                          | Artifactory   | Google Container Registry (gcr.io) |
| ----------- | ------------------------------ | -------------------------------- | ------------- | ---------------------------------- |
| Workflow    | github -> docker build         | pipeline supported               | N/A           | vender lock-in: gcloud sdk         |
| Auth        | user/group: NO ldap/saml/oauth | read/write control: NO ldap/saml | ldap/saml     | limited ldap support               |
| Performance | uneven                         | stable                           | N/A           | highly available                   |
| Pricing     | inexpensive                    | relatively inexpensive           | steep pricing | low cost                           |

### Conclusion

- Docker Hub

Good for opensource project, Bad for enterprise proprietary applications.

- CoreOS (quay.io)

Clean, intuitive and streamlined interface, pipeline workflow, fine-grained
read/write access control, limited ldap/saml enterprise support.

- Artifactory

More about a artifact management repository, not a dedicated docker registry.

- Google Container Registry (gcr.io)

Easy to work with Google cloud service, but locked-in by vender.
