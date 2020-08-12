# Docker Network Types

- Host Networking

The container shares the same IP address and network namespace as that of the
host. Services running inside of this container have the same network
capabilities as services running directly on the host.

- Bridge Networking

The container runs in a private network internal to the host. Communication is
open to other containers in the same network. Communication with services
outside of the host goes through network address translation (NAT) before
exiting the host. (This is the default mode of networking when the `--net`
option isn't specified)

- Custom bridge network

This is the same as Bridge Networking but uses a bridge explicitly created for
this (and other) containers. An example of how to use this would be a container
that runs on an exclusive "database" bridge network. Another container can have
an interface on the default bridge and the database bridge, enabling it to
communicate with both networks.

- Container-defined Networking

A container can share the address and network configuration of another
container. This type enables process isolation between containers, where each
container runs one service but where services can still communicate with one
another on the `localhost` address.

- No Networking

This option disables all networking for the container.

# Docker linux capabilities

- Docker allowed by default

| Linux                | Docker           | Capability Description                                                                                                       |
| ---                  | ---              | ---                                                                                                                          |
| CAP_SETPCAP          | SETPCAP          | Modify process capabilities                                                                                                  |
| CAP_MKNOD            | MKNOD            | Create special file using mknode                                                                                             |
| CAP_AUDIT_WRITE      | AUDIT_WRITE      | Write records to kernel auditing log                                                                                         |
| CAP_CHOWN            | CHOWN            | Make arbitrary changes to file UIDs and GIDs                                                                                 |
| CAP_NET_RAW          | NET_RAW          | Use RAW and PACKET sockets                                                                                                   |
| CAP_DAC_OVERRIDE     | DAC_OVERRIDE     | Bypass file read, write, and execute permission checks                                                                       |
| CAP_FOWNER           | FOWNER           | Bypass permission checks on operations that normally require the file system UID of the process to match the UID of the file |
| CAP_FSEDIT           | FSEDIT           | Don't clear set-user-ID and set-group-ID permission bits when a file is modified                                             |
| CAP_KILL             | KILL             | Bypass permission checks for sending signals                                                                                 |
| CAP_SETGID           | SETGID           | Make arbitrary manipulations of process GIDs and supplementary GID list                                                      |
| CAP_SETUID           | SETUID           | Make arbitrary manipulations of process UIDs                                                                                 |
| CAP_NET_BIND_SERVICE | NET_BIND_SERVICE | Bind a socket to internet domain privileged ports (port numbers less than 1024)                                              |
| CAP_SYS_CHROOT       | SYS_CHROOT       | Use chroot, change root directory                                                                                            |
| CAP_SETFCAP          | SETFCAP          | Set file capabilities                                                                                                        |

- Docker disallowed by default

| Linux               | Docker          | Capability Description                                                                                         |
| ---                 | ---             | ---                                                                                                            |
| CAP_SYS_MODULE      | SYS_MODULE      | Load and unload kernel modules                                                                                 |
| CAP_SYS_RAWIO       | SYS_RAWIO       | Perform I/O port operations                                                                                    |
| CAP_SYS_PACCT       | SYS_PACCT       | Use acct, switch process accounting on or off                                                                  |
| CAP_SYS_ADMIN       | SYS_ADMIN       | Perform a range of system administration operations                                                            |
| CAP_SYS_NICE        | SYS_NICE        | Raise process nice value and change the nice value for arbitrary process                                       |
| CAP_SYS_RESOURCE    | SYS_RESOURCE    | Override resource limits                                                                                       |
| CAP_SYS_TIME        | SYS_TIME        | Set system clock; set real-time clock                                                                          |
| CAP_SYS_TTY_CONFIG  | SYS_TTY_CONFIG  | Use vhangup; employ various privileged ioctl operations on virtual terminals                                   |
| CAP_AUDIT_CONTROL   | AUDIT_CONTROL   | Enable and disable kernel auditing; change auditing filter rules; retrieve auditing status and filtering rules |
| CAP_MAC_ADMIN       | MAC_ADMIN       | Allow MAC configuration of state changes                                                                       |
| CAP_MAC_OVERRIDE    | MAC_OVERRIDE    | Overried Mandatory Access Control (MAC)                                                                        |
| CAP_NET_ADMIN       | NET_ADMIN       | Perform various network-related operations                                                                     |
| CAP_SYSLOG          | SYSLOG          | Perofrm privileged syslog operations                                                                           |
| CAP_DAC_READ_SEARCH | DAC_READ_SEARCH | Bypass file read permission checks and directory read and execute permission checks                            |
| CAP_LINUX_IMMUTABLE | LINUX_IMMUTABLE | Set the FS_APPEND and FS_IMMUTABLE_FL i-node flags                                                             |
| CAP_NET_BROADCAST   | NET_BROADCAST   | Make socket broadcast, and listen to multicasts                                                                |
| CAP_IPC_LOCK        | IPC_LOCK        | Lock memory (mlock, mlockall, mmap, shmctl)                                                                    |
| CAP_IPC_OWNER       | IPC_OWNER       | Bypass permission checks for operations on System V IPC objects                                                |
| CAP_SYS_PTRACE      | SYS_PTRACE      | Trace arbitrary processes using ptrace                                                                         |
| CAP_SYS_ROOT        | SYS_ROOT        | Use reboot and kexec_load, reboot and load a new kernel for later execution                                    |
| CAP_LEASE           | LEASE           | Establish leases on arbitrary files                                                                            |
| CAP_WAKE_ALARM      | WAKE_ALARM      | Trigger something that will wake up the system                                                                 |
| CAP_BLOCK_SUSPEND   | BLOCK_SUSPEND   | Employ features that can block system suspend                                                                  |
