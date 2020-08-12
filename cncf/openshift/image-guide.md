# General Container Image Guidelines

- Reuse Images

Wherever possible, we recommend that you base your image on an appropriate
upstream image using the FROM statement. This ensures your image can easily pick
up security fixes from an upstream image when it is updated, rather than you
having to update your dependencies directly.

In addition, use tags in the FROM instruction (for example, rhel:rhel7) to make
it clear to users exactly which version of an image your image is based on.
Using a tag other than latest ensures your image is not subjected to breaking
changes that might go into the latest version of an upstream image.

- Maintain Compatibility Within Tags

When tagging your own images, we recommend that you try to maintain backwards
compatibility within a tag. For example, if you provide an image named foo and
it currently includes version 1.0, you might provide a tag of foo:v1. When you
update the image, as long as it continues to be compatible with the original
image, you can continue to tag the new image foo:v1, and downstream consumers of
this tag will be able to get updates without being broken.

If you later release an incompatible update, then you should switch to a new
tag, for example foo:v2. This allows downstream consumers to move up to the new
version at will, but not be inadvertently broken by the new incompatible image.
Any downstream consumer using foo:latest takes on the risk of any incompatible
changes being introduced.

- Avoid Multiple Processes

We recommend that you do not start multiple services, such as a database and
SSHD, inside one container. This is not necessary because containers are
lightweight and can be easily linked together for orchestrating multiple
processes. OKD allows you to easily colocate and co-manage related images by
grouping them into a single pod.

This colocation ensures the containers share a network namespace and storage for
communication. Updates are also less disruptive as each image can be updated
less frequently and independently. Signal handling flows are also clearer with a
single process as you do not need to manage routing signals to spawned
processes.

- Use exec in Wrapper Scripts

See the "Always exec in Wrapper Scripts" section of the Project Atomic
documentation for more information.

Also note that your process runs as PID 1 when running in a container. This
means that if your main process terminates, the entire container is stopped,
killing any child processes you may have launched from your PID 1 process.

See the "Docker and the PID 1 zombie reaping problem" blog article for
additional implications. Also see the "Demystifying the init system (PID 1)"
blog article for a deep dive on PID 1 and init systems.

- Clean Temporary Files

All temporary files you create during the build process should be removed. This
also includes any files added with the ADD command. For example, we strongly
recommended that you run the yum clean command after performing yum install
operations.

You can prevent the yum cache from ending up in an image layer by creating your
RUN statement as follows:

```Dockerfile
RUN yum -y install mypackage && yum -y install myotherpackage && yum clean all -y
```

Note that if you instead write:

```Dockerfile
RUN yum -y install mypackage
RUN yum -y install myotherpackage && yum clean all -y
```

Then the first yum invocation leaves extra files in that layer, and these files
cannot be removed when the yum clean operation is run later. The extra files are
not visible in the final image, but they are present in the underlying layers.

The current container build process does not allow a command run in a later
layer to shrink the space used by the image when something was removed in an
earlier layer. However, this may change in the future. This means that if you
perform an rm command in a later layer, although the files are hidden it does
not reduce the overall size of the image to be downloaded. Therefore, as with
the yum clean example, it is best to remove files in the same command that
created them, where possible, so they do not end up written to a layer.

In addition, performing multiple commands in a single RUN statement reduces the
number of layers in your image, which improves download and extraction time.

- Place Instructions in the Proper Order

The container builder reads the Dockerfile and runs the instructions from top to
bottom. Every instruction that is successfully executed creates a layer which
can be reused the next time this or another image is built. It is very important
to place instructions that will rarely change at the top of your Dockerfile.
Doing so ensures the next builds of the same image are very fast because the
cache is not invalidated by upper layer changes.

For example, if you are working on a Dockerfile that contains an ADD command to
install a file you are iterating on, and a RUN command to yum install a package,
it is best to put the ADD command last:

```Dockerfile
FROM foo
RUN yum -y install mypackage && yum clean all -y
ADD myfile /test/myfile
```

This way each time you edit myfile and rerun podman build or docker build, the
system reuses the cached layer for the yum command and only generates the new
layer for the ADD operation.

If instead you wrote the Dockerfile as:

```Dockerfile
FROM foo
ADD myfile /test/myfile
RUN yum -y install mypackage && yum clean all -y
```

Then each time you changed myfile and reran podman build or docker build, the
ADD operation would invalidate the RUN layer cache, so the yum operation would
need to be rerun as well.

- Mark Important Ports

See the "Always EXPOSE Important Ports" section of the Project Atomic
documentation for more information.

- Set Environment Variables

It is good practice to set environment variables with the ENV instruction. One
example is to set the version of your project. This makes it easy for people to
find the version without looking at the Dockerfile. Another example is
advertising a path on the system that could be used by another process, such as
JAVA_HOME.

- Avoid Default Passwords

It is best to avoid setting default passwords. Many people will extend the image
and forget to remove or change the default password. This can lead to security
issues if a user in production is assigned a well-known password. Passwords
should be configurable using an environment variable instead. See the Using
Environment Variables for Configuration topic for more information.

If you do choose to set a default password, ensure that an appropriate warning
message is displayed when the container is started. The message should inform
the user of the value of the default password and explain how to change it, such
as what environment variable to set.

- Avoid SSHD

It is best to avoid running SSHD in your image. You can use the podman exec or
docker exec command to access containers that are running on the local host.
Alternatively, you can use the oc exec command or the oc rsh command to access
containers that are running on the OKD cluster. Installing and running SSHD in
your image opens up additional vectors for attack and requirements for security
patching.

- Use Volumes for Persistent Data

Images should use a Docker volume for persistent data. This way OKD mounts the
network storage to the node running the container, and if the container moves to
a new node the storage is reattached to that node. By using the volume for all
persistent storage needs, the content is preserved even if the container is
restarted or moved. If your image writes data to arbitrary locations within the
container, that content might not be preserved.

All data that needs to be preserved even after the container is destroyed must
be written to a volume. Container engines support a readonly flag for containers
which can be used to strictly enforce good practices about not writing data to
ephemeral storage in a container. Designing your image around that capability
now will make it easier to take advantage of it later.

Furthermore, explicitly defining volumes in your Dockerfile makes it easy for
consumers of the image to understand what volumes they need to define when
running your image.
