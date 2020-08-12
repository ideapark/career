# Why pause per Pod

- dead process reaper

Every PID namespace is equipped with a task that assumes the role taken by init
in the global picture. One of the purposes of init is to call *wait4* for
orphaned tasks, and this must likewise be done by the namespace-specific init
variant. A pointer to the task structure of this task is stored in *child_reaper*.

- pod scope network namespace

All contianers in the same pod shares the same network namespace, so they can
reach others through `localhost` network.

- lifecycle management

Pod lifecycle is managed with this pause cotainer lifecycle.

NOTE: The `pause` container was initially designed to act as `init` process
within a PID namespace shared by all containers in the Pod. It performed the
function of reaping zombie processes when a container died. PID namespace
sharing is now disabled by default, so unless it has been explicitly enabled in
the kubelet, all containers run their process as PID 1.
