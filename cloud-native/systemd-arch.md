System Management Daemon
========================

~~~
 +--- systemd Utilities ---------------------------------------------------------------------+
 |                                                                                           |
 | systemctl        journalctl        loginctl                                               |
 | systemd-notify   systemd-analyze   systemd-cgls   systemd-cgtop   systemd-nspawn          |
 +-------------------------------------------------------------------------------------------+

 +--- systemd Daemons --+ +--- systemd Targets ----------------------------------------------+
 |    systemd           | |                       multi-user    graphical       user-session |
 | journald  networkd   | |  bootmode basic     dbus telephony   user-       display service |
 | logind  user session | |  shutdown reboot    dlog logind     session      tizen service   |
 +----------------------+ +------------------------------------------------------------------+

 +--- systemd Core --------------------------------------------------------------------------+
 |                     unit                      login                                       |
 |  manager  service timer mount target   multiseat inhibit   namespace log                  |
 |  systemd  snapshot path socket swap     session  pam         cgroup dbus                  |
 +-------------------------------------------------------------------------------------------+

 +--- systemd Libraries ---------------------------------------------------------------------+
 |  dbus-1   libpam   libcap   libcryptsetup   tcpwrapper   libaudit   libnotify             |
 +-------------------------------------------------------------------------------------------+

 +-------------------------------------------------------------------------------------------+
 | Linux Kernel            cgroups     autofs     kdbus                                      |
 +-------------------------------------------------------------------------------------------+
~~~
