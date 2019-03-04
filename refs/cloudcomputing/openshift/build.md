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
