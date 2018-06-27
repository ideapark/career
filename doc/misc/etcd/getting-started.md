# Getting started with etcd

etcd is an open-source distributed key value store that provides shared
configuration and service discovery for Container Linux clusters. etcd runs on
each machine in a cluster and gracefully handles leader election during network
partitions and the loss of the current leader.

Application containers running on your cluster can read and write data into
etcd. Common examples are storing database connection details, cache settings,
feature flags, and more. This guide will walk you through a basic example of
reading and writing to etcd then proceed to other features like TTLs,
directories and watching a prefix. This guide is way more fun when you've got at
least one Container Linux machine up and running — try it on Amazon EC2 or
locally with Vagrant.
