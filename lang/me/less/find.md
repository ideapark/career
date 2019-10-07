# find

### Find everything that you want

> find /home/p -iname '*linux*' -type d --ls

---

```
[p@thinkpad p]$ find /home/p/linux/ -iname '*linux*' -type d -ls
 17301647  4 drwxr-xr-x 21 p p  4096 Jun 17 00:35 /home/p/linux/
 17831786  4 drwxr-xr-x  7 p p  4096 Jun 16 22:37 /home/p/linux/arch/um/os-Linux
 18227026 40 drwxr-xr-x 25 p p 36864 Jun 16 22:38 /home/p/linux/include/linux
 18357487  4 drwxr-xr-x  4 p p  4096 Jun 16 22:38 /home/p/linux/security/selinux
 18221646  4 drwxr-xr-x  2 p p  4096 Jun 16 22:37 /home/p/linux/fs/xfs/linux-2.6
 17568159  4 drwxr-xr-x  5 p p  4096 Jun 16 22:37 /home/p/linux/Documentation/video4linux
```
