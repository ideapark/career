# Features that units are able to implement

- socket-based activation:

Sockets associated with a service are best broken out of the daemon itself in
order to be handled separately. This provides a number of advantages, such as
delaying the start of a service until the associated socket is first accessed.
This also allows the system to create all sockets early in the boot process,
making it possible to boot the associated services in parallel.

- bus-based activation:

Units can also be activated on the bus interface provided by D-Bus. A unit can
be started when an associated bus is published.

- path-based activation:

A unit can be started based on activity on or the availability of certain
filesystem paths. This utilizes inotify.

- device-based activation:

Units can also be started at the first availability of associated hardware by
leveraging udev events.

- implicit dependency mapping:

Most of the dependency tree for units can be built by systemd itself. You can
still add dependency and ordering information, but most of the heavy lifting is
taken care of for you.

- instances and templates:

Template unit files can be used to create multiple instances of the same general
unit. This allows for slight variations or sibling units that all provide the
same general function.

- easy security hardening:

Units can implement some fairly good security features by adding simple
directives. For example, you can specify no or read-only access to part of the
filesystem, limit kernel capabilities, and assign private /tmp and network
access.

- drop-ins and snippets:

Units can easily be extended by providing snippets that will override parts of
the system’s unit file. This makes it easy to switch between vanilla and
customized unit implementations.
