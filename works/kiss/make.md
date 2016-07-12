# make

### Target, Depend, Action

> make

```
[lockrecv@thinkpad lockrecv]$ pstree
systemd-+-dbus-daemon
        |-dhcpcd
        |-docker-+-docker-containe---8*[{docker-containe}]
        |        `-10*[{docker}]
        |-gpg-agent
        |-login---bash---tmux
        |-polkitd-+-{JS GC Helper}
        |         |-{JS Sour~ Thread}
        |         |-{gdbus}
        |         |-{gmain}
        |         `-{polkitd}
        |-rtkit-daemon---2*[{rtkit-daemon}]
        |-systemd-+-(sd-pam)
        |         |-dbus-daemon
        |         |-gvfs-udisks2-vo-+-{gdbus}
        |         |                 `-{gmain}
        |         |-gvfsd-+-{gdbus}
        |         |       `-{gmain}
        |         |-gvfsd-fuse-+-{gdbus}
        |         |            |-{gmain}
        |         |            |-{gvfs-fuse-sub}
        |         |            `-2*[{gvfsd-fuse}]
        |         |-gvfsd-metadata-+-{gdbus}
        |         |                `-{gmain}
        |         |-pulseaudio-+-{alsa-sink-ALC26}
        |         |            `-{alsa-source-ALC}
        |         `-xfconfd
        |-systemd-journal
        |-systemd-logind
        |-systemd-network
        |-systemd-resolve
        |-systemd-timesyn---2*[{sd-resolve}]
        |-systemd-udevd
        |-tmux-+-bash---pstree
        |      `-bash---make---sh---make---sh---cc---cc1
        |-udisksd-+-{cleanup}
        |         |-{gdbus}
        |         |-{gmain}
        |         `-{probing-thread}
        |-upowerd-+-{gdbus}
        |         `-{gmain}
        `-wpa_supplicant
```
