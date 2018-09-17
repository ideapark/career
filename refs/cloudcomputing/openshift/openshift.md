# Openshift vs Kubernetes

```text
o: OpenShift
k: Kubernetes

ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
o Project                                                                         o
o                                                                                 o
o  kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk  o
o  k Namespace                                                                 k  o
o  k                                                                           k  o
o  k ooooooooooooooooooo         ooooooooooooooooooooo                         k  o
o  k o Source to Image o         o Integrated Docker o                         k  o
o  k o     (S2I)       o         o      Registry     o                         k  o
o  k ooooooooooooooooooo         ooooooooooooooooooooo                         k  o
o  k         |                             |                                   k  o
o  k ooooooooooooooooooo                   |                 ooooooooooooooooo k  o
o  k o      Build      o         ooooooooooooooooooooo       o Deployment    o k  o
o  k o  Configuration  o---------o   Image Stream    o-------o Configuration o k  o
o  k ooooooooooooooooooo         ooooooooooooooooooooo       ooooooooooooooooo k  o
o  k                                                                 |         k  o
o  k kkkkkkkkkkkkkkkkkkkkk       kkkkkkkkkkkkkkkkkkkkk       kkkkkkkkkkkkkkkkk k  o
o  k k Persistent Volume k-------k        Pods       k-------k   Replication k k  o
o  k k       Claim       k       kkkkkkkkkkkkkkkkkkkkk       kkkkkkkkkkkkkkkkk k  o
o  k kkkkkkkkkkkkkkkkkkkkk                 |                                   k  o
o  k          |                            |                                   k  o
o  k kkkkkkkkkkkkkkkkkkkkk       kkkkkkkkkkkkkkkkkkkkk       ooooooooooooooooo k  o
o  k k Persistent Volume k       k       Services    k-------o     Routes    o k  o
o  k kkkkkkkkkkkkkkkkkkkkk       kkkkkkkkkkkkkkkkkkkkk       ooooooooooooooooo k  o
o  k                                       |                         |         k  o
o  k                                       +------------+------------+         k  o
o  k                                                    |                      k  o
o  k                             ooooooooooooooooooooooooooooooooooooooooooooo k  o
o  k                             o     Software Defined Network (SDN)        o k  o
o  k                             ooooooooooooooooooooooooooooooooooooooooooooo k  o
o  k                                                                           k  o
o  kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk  o
o                                                                                 o
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
```
