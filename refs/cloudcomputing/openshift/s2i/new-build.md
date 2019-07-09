oc new-build --name <build-name> <imagestream>:<github-src> --strategy=docker|pipeline|source

- Source

This uses Source-to-Image to produce ready-to-run images by injecting applica‐
tion source (or other assets) into a builder image.

- Docker

This uses docker build to take a Dockerfile and associated source files and cre‐
ate a runnable image.

- Pipeline

This uses Jenkins and a workflow defined by a Jenkinsfile to create a pipeline
for building a runnable image.

- Custom

This uses your own custom image to control the build process for creating the
runnable image.
