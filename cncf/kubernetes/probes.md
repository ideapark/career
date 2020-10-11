# liveness vs readiness probe

*liveness* probe helps keep apps healthy by ensuringg unhealthy containers are
restarted automatically.

*readiness* probe is invoked periodically and determines whether the specific
pod should receive client requests or not.

Unlike liveness probes, if a container fails the readiness check, it won't be
killed or restarted. This is an important distinction between liveness and
readiness probes. Liveness probes keep pods healthy by killing off unhealthy
containers and replacing them with new, healthy ones, whereas readiness probes
make sure that only pods that are ready to serve requests receive them. This is
mostly necessary during container start up, but it's also useful after the
container has been running for a while.

## probe settings

- delay

How long after a pod has been started, before the first check using the probe is
run

- timeout

How long the probes is given to respond with a result before it is deemed to
have failed

- period

How long after a previous check using a probe to wait before the next check is
run

- #success

The number of successful checks in a row required for the probe to be deemed as
having passed

- #failure

The number of unsuccessful checks in a row required for the probe to be deemed
as having failed

## example

Liveness:  exec [powershift image alive]
           delay=0s
           timeout=1s
           period=10s
           #success=1
           #failure=3

Readiness: http-get http://:8080/readyz
           delay=0s
           timeout=1s
           period=10s
           #success=1
           #failure=3
