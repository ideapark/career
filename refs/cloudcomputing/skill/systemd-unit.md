# systemd units

- service

application on the server that is launched by systemd; how it should start/stop;
when it should be started; under what circumstances it should be restarted; and
any resource controls that should be applied to it.

- scope

a process or group of processes which are not launched by systemd (i.e. fork),
like a service, resource controls may be applied.

- slice

organizes a hierarchy in which scope and service units are placed. a slice may
contain slice, scope, or service units; processes are attached to service and
scope units only, not to slices. The hierarchy is intended to be unified,
meaning a process may only belong to a single leaf node.
