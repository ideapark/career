# OKD-Specific Container Image Guidelines

- Enable Images for Source-To-Image (S2I)

For images that are intended to run application code provided by a third party,
such as a Ruby image designed to run Ruby code provided by a developer, you can
enable your image to work with the Source-to-Image (S2I) build tool. S2I is a
framework which makes it easy to write images that take application source code
as an input and produce a new image that runs the assembled application as
output.

For example, this Python image defines S2I scripts for building various versions
of Python applications.

For more details about how to write S2I scripts for your image, see the S2I
Requirements topic.

- Support Arbitrary User IDs

By default, OKD runs containers using an arbitrarily assigned user ID. This
provides additional security against processes escaping the container due to a
container engine vulnerability and thereby achieving escalated permissions on
the host node.

For an image to support running as an arbitrary user, directories and files that
may be written to by processes in the image should be owned by the root group
and be read/writable by that group. Files to be executed should also have group
execute permissions.

Adding the following to your Dockerfile sets the directory and file permissions
to allow users in the root group to access them in the built image:

```Dockerfile
RUN chgrp -R 0 /some/directory && \
    chmod -R g=u /some/directory
```

Because the container user is always a member of the root group, the container
user can read and write these files. The root group does not have any special
permissions (unlike the root user) so there are no security concerns with this
arrangement. In addition, the processes running in the container must not listen
on privileged ports (ports below 1024), since they are not running as a
privileged user.

Because the user ID of the container is generated dynamically, it will not have
an associated entry in /etc/passwd. This can cause problems for applications
that expect to be able to look up their user ID. One way to address this problem
is to dynamically create a passwd file entry with the container’s user ID as
part of the image’s start script. This is what a Dockerfile might include:

```Dockerfile
RUN chmod g=u /etc/passwd
ENTRYPOINT [ "uid_entrypoint" ]
USER 1001
```

Where uid_entrypoint contains:

```bash
if ! whoami &> /dev/null; then
  if [ -w /etc/passwd ]; then
    echo "${USER_NAME:-default}:x:$(id -u):0:${USER_NAME:-default} user:${HOME}:/sbin/nologin" >> /etc/passwd
  fi
fi
```

For a complete example of this, see this Dockerfile.

Lastly, the final USER declaration in the Dockerfile should specify the user ID
(numeric value) and not the user name. This allows OKD to validate the authority
the image is attempting to run with and prevent running images that are trying
to run as root, because running containers as a privileged user exposes
potential security holes. If the image does not specify a USER, it inherits the
USER from the parent image.

- Set Image Metadata

Defining image metadata helps OKD better consume your container images, allowing
OKD to create a better experience for developers using your image. For example,
you can add metadata to provide helpful descriptions of your image, or offer
suggestions on other images that may also be needed.

See the Image Metadata topic for more information on supported metadata and how
to define them.

- Clustering

You must fully understand what it means to run multiple instances of your image.
In the simplest case, the load balancing function of a service handles routing
traffic to all instances of your image. However, many frameworks need to share
information in order to perform leader election or failover state; for example,
in session replication.

Consider how your instances accomplish this communication when running in OKD.
Although pods can communicate directly with each other, their IP addresses
change anytime the pod starts, stops, or is moved. Therefore, it is important
for your clustering scheme to be dynamic.

- Logging

It is best to send all logging to standard out. OKD collects standard out from
containers and sends it to the centralized logging service where it can be
viewed. If you need to separate log content, prefix the output with an
appropriate keyword, which makes it possible to filter the messages.

If your image logs to a file, users must use manual operations to enter the
running container and retrieve or view the log file.

- Liveness and Readiness Probes

Document example liveness and readiness probes that can be used with your image.
These probes will allow users to deploy your image with confidence that traffic
will not be routed to the container until it is prepared to handle it, and that
the container will be restarted if the process gets into an unhealthy state.

- Templates

Consider providing an example template with your image. A template will give
users an easy way to quickly get your image deployed with a working
configuration. Your template should include the liveness and readiness probes
you documented with the image, for completeness.
