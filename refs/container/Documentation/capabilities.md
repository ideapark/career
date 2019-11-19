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
