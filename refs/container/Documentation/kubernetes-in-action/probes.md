# liveness vs readiness probe

liveness probe helps keep apps healthy by ensuringg unhealthy containers are
restarted automatically.

readiness probe is invoked periodically and determines whether the specific pod
should receive client requests or not.

Unlike liveness probes, if a container fails the readiness check, it won't be
killed or restarted. This is an important distinction between liveness and
readiness probes. Liveness probes keep pods healthy by killing off unhealthy
containers and replacing them with new, healthy ones, whereas readiness probes
make sure that only pods that are ready to serve requests receive them. This is
mostly necessary during container start up, but it's also useful after the
container has been running for a while.
