# Operator Framework (TECH-PREVIEW)

An open source toolkit designed to manage Kubernetes native applications, called
Operators, in a more effective, automated, and scalable way.

An Operator is a method of packaging, deploying and managing a Kubernetes
application. A Kubernetes application is an application that is both deployed on
Kubernetes and managed using the Kubernetes APIs and kubectl tooling. To be able
to make the most of Kubernetes, you need a set of cohesive APIs to extend in
order to service and manage your applications that run on Kubernetes. You can
think of Operators as the runtime that manages this type of application on
Kubernetes.

Conceptually, an Operator takes human operational knowledge and encodes it into
software that is more easily packaged and shared with consumers. Think of an
Operator as an extension of the software vendor's engineering team that watches
over your Kubernetes environment and uses its current state to make decisions in
milliseconds. Operators follow a maturity model that ranges from basic
functionality to having specific logic for an application. Advanced Operators
are designed to handle upgrades seamlessly, react to failures automatically, and
not take shortcuts, like skipping a software backup process to save time.

## Operator Components

- Operator SDK

Enables developers to build Operators based on their expertise without requiring
knowledge of Kubernetes API complexities.

- Operator Lifecycle Management

Oversees installation, updates, and management of the lifecycle of all of the
Operators (and their associated services) running across a Kubernetes cluster.

- Operator Metering

Enables usage reporting for Operators that provide specialized services.
