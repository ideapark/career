---
author: Zhou Peng <park@ideapark.io>
description: Cloud-Native & Cloud-Native Infrastructure
---

# What's Cloud-Native: Architecture + Engineering + People

~~~
                          +--------------------------------------------+
                          |          A.R.C.H.I.T.E.C.T.U.R.E           |
                          |--------------------------------------------|
                          | Elastic | Destributed | High Availiability |
                          |--------------------------------------------|
                          | Multi Tenant | Auto Ops | Self Service     |
                          |--------------------------------------------|
                          |           Micro-service architecture       |
                          |--------------------------------------------|
                          |        Cloud Infrastructure & PaaS         |
                          +--------------------------------------------+
                                               ..
                                              .  .
                                             .    .
                                            ########
                                           #CUSTOMER#
                                          #   VALUE  #
                                         # ########## #
                                        .              .
                                       .   Fast Scale   .
                                      .  Agile Reliable  .
                                     .      Efficient     .
                                    .                      .
                                   ... . . . . . . . . . . ..
      +-----------------------+                                    +-----------------------+
      | E.N.G.I.N.E.E.R.I.N.G |                                    |      P.E.O.P.L.E      |
      |-----------------------|                                    |-----------------------|
      |      DevOps           |                                    | Full Functional Team  |
      |-----------------------|                                    |-----------------------|
      | Micro-service CI/CD   |                                    | Agile Team            |
      |-----------------------|                                    |-----------------------|
      | Develop Environment   |                                    | Full Stack Engineer   |
      +-----------------------+                                    +-----------------------+
~~~

# Cloud-Native Infrastructure Pillars & Capability Level

## 4 Pillars

~~~
S C A L A B L E            R E S I L L I E N T       O B S E R V A B L E        S E C U R I T Y
 Horizontal AutoScaler       Retry                     Monitoring                 Authentication
 High Availability           Timeout                   Logging                    Authorization
                             Circuit Breaker           Metrics                    Audit
                             Load Balance              Tracing                    mTLS
------------------------------------------------------------------------------------------------
                                            API DRIVEN
~~~

## 2 Capability Level

- As Code: Versioned, Repeatable (Ansible, Terraform)
- As Software: API driven, Self-Awareness, Auto-Pilot (Kubernetes, Operator)

A cloud native application is engineered to run on a platform and is designed
for *resiliency*, *agility*, *operability*, and *observability*:

1. *Resiliency*

embraces failures instead of trying to prevent them; it takes advantage of the
dynamic nature of running on a platform.

2. *Agility*

allows for fast deployments and quick iterations.

3. *Operability*

adds control of application life cycles from inside the application instead of
relying on external processes and monitors.

4. *Observability*

provides information to answer questions about application state.

CLOUD-NATIVE APPLICATION IS DESIGNED FOR THE CLOUD AND RUN ON THE CLOUD.

## Infrastructure as Code/Software

A fundamental difference between infrastructure as code and infrastructure as
software is that software continually runs and will create or mutate
infrastructure based on the reconciler pattern.

    Ansible (code) ...VS... Kubernetes (software)
