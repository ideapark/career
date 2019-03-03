# OpenShift 4: A NoOps Platform

## What does "NoOps" mean?

- For Developer.

  1. Don't consume systems -- consume APIs
  2. Don't deploy software -- have the provider deploy it for you
  3. Don's start with a large framework -- write small pieces of software as
     building blocks and connect them with data and events ranther than disks
     and databases

- For Operations team

  1. Don't manage systems -- automate their management
  2. Don't deploy software -- define a deployment pipeline
  3. Don't couple all of your services together in a single failure domain --
     spread them out with infrastructure automation and connect them with
     observability.

## How do we get there?

- The standard approach

  1. Automate and standardize infrastructure in service of the application
  2. Blend deployment and development without limiting the developer
  3. Make running, auditing, and securing the hundredth service, function,
     application, or stack as easy as the first

- The OpenShift 4 approach

  1. Make clusters self-describing -- don't just run on a cloud, tell it what to
     do
  2. Machines and the operating system that run them exist to serve the cluster
  3. Control the host state from the cluster, and minimize the drift hosts may
     have
  4. Every important part of the system needs a babysitter reconciling and
     fixing problems
  5. Make failure and recovery an expected part of *every* aspect of the system
  6. Everything must be configured via an API
  7. Use Kubernetes to run Kubernetes
  8. Updates have to be no big deal -- if an update isn't pushing a buttion,
     it's wrong
  9. Every component has to be easy to monitor and debug, and conversely
     summarizing and monitoring everything has to also be easy
