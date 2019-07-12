# OpenShift Build

A build is the process of transforming input parameters into a resulting object.
Most often, builds are used to transform source code into runnable container
image.

```text
    Build Strategy             +     Build Input        =   Build Output
    ------------------------         ----------------       ----------------
    1. source-to-image (s2i)         1. git                 1. image
    2. pipeline                      2. dockerfile          2. artificates
    3. docker                        3. binary
    4. custom                        4. image
                                     5. input secrets
                                     6. external artifacts
```

## Input precedence (highest:1 -> lowest:6)

1. Inline Dockerfile definitions
2. Content extracted from existing images
3. Git repositories
4. Binary (Local) inputs
5. Input secrets and ConfigMaps
6. External artifacts

## Triggers

1. Webhook
  - GitHub
  - GitLab
  - Bitbucket
2. Image change
3. Configuration change

## Run Policy

1. Parallel
2. Serial
3. SerialLatestOnly

- Changing Parallel to Serial or SerialLatestOnly and triggering a new build
  from this configuration will cause the new build to wait until all parallel
  builds complete as the serial build can only run alone.

- Changing Serial to SerialLatestOnly and triggering a new build will cause
  cancellation of all existing builds in queue, except the currently running
  build and the most recently created build. The newest build will execute next.

## Chaining Build

For compiled languages (Go, C, C++, Java, etc.), including the dependencies
necessary for compilation in the application image might increase the size of
the image or introduce vulnerabilities that can be exploited.

To avoid these problems, two builds can be chained together: one that produces
the compiled artifact, and a second build that places that artifact in a
separate image that runs the artifact. In the following example, a
Source-to-Image is combined with a Docker build to compile an artifact that is
then placed in a separate runtime image.

```text
+-----------------+   +---------------+
|S2I Builder Image|   | Source        |
+-----------------+   +---------------+
        |                      |
        +-----------+----------+
                    |
                    v
        +----------------------+
        |       S2I Build      |
        +----------------------+
                    |
                    v
    +------------------------------+  +---------------+ +------------+
    | Image (with binary artifact) |  | Runtime Image | | Dockerfile |
    +------------------------------+  +---------------+ +------------+
                    |                         |                |
                    +-------------------------+----------------+
                                              |
                                              v
                              +----------------------------------+
                              | Docker Build (with image source) |
                              +----------------------------------+
                                              |
                                              v
                           +----------------------------------------+
                           | Runtime Image (with compiled artifact) |
                           +----------------------------------------+
```
