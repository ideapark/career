Process Management
==================

pid = fork();                         /* create a process identical to the parent */
pid = waitpid(pid, &statloc, opts);   /* wait for a child to terminate */
s = wait(&status);                    /* old version of waitpid */
s = execve(name, argv, envp);         /* repalce a process core image */
exit(status);                         /* terminate process execution and return status */
size = brk(addr);                     /* set the size of the data segment */
pid = getpid();                       /* return the caller's process pid */
pid = getpgrp();                      /* return the id of the caller's process group */
pid = setid();                        /* create a new session and return its proc. group id */
l = ptrace(req, pid, addr, data);     /* used for debugging */

Signals
=======

s = sigaction(sig, &act, &oldact);    /* define action to take on signals */
s = sigreturn(&context);              /* return from a signal */
s = sigprocmask(how, &set, &old);     /* examine or change the signal mask */
s = sigpending(set);                  /* get the set of blocked signals */
s = sigsuspend(sigmask);              /* repalce the signal mask and suspend the process */
s = kill(pid, sig);                   /* send a signal to a process */
residual = alarm(setconds);           /* setup alarm clock */
s = pause();                          /* suspend the caller until next signal */

File Management
===============

fd = creat(name, mode);               /* obsolete way to create a new file */
fd = mknod(name, mode, addr);         /* create a regular, special, or directory i-node */
fd = open(file, how, ...);            /* open a file for reading, writing, or both */
s = close(fd);                        /* close an open file */
n = read(fd, buffer, nbytes);         /* read data from a file into a buffer */
n = write(fd, buffer, nbytes);        /* write data from a buffer into file */
pos = lseek(fd, offset, whence);      /* move the file pointer */
s = stat(name, &buf);                 /* get a file's status information */
s = fstat(fd, &buf);                  /* get a file's status information */
fd = dup(fd);                         /* allocate a new file descriptor for an open file */
s = pipe(&fd[0]);                     /* create a pipe */
s = ioctl(fd, request, argp);         /* perform specifial operations on a file */
s = access(name, amode);              /* check file's accessibility */
s = rename(old, new);                 /* give a file a new name */
s = fcntl(fd, cmd, ...);              /* file locking or other operations */

Dir. & File System Mgt.
=======================

s = mkdir(name, mode);                /* create a new directory */
s = rmdir(name);                      /* remove an empty directory */
s = link(name1, name2);               /* create new entry, name2, pointing to name1 */
s = unlink(name);                     /* remove a directory entry */
s = mount(special, name, flag);       /* mount a file system */
s = umount(special);                  /* umount a file system */
s = sync();                           /* flush all cached blocks to disk */
s = chdir(dirname);                   /* change the working directory */
s = chroot(dirname);                  /* change the root directory */

Protection
==========

s = chmod(name, mode);                /* change a file's protection bits */
uid = getuid();                       /* get the caller's uid */
gid = getgid();                       /* get the caller's gid */
s = setuid(uid);                      /* set the caller's uid */
s = setgid(gid);                      /* set the caller's gid */
s = chown(name, owner, group);        /* change a file's owner and group */
oldmask = umask(complmode);           /* change the mode mask */

Time Management
===============

seconds = time(&seconds);             /* get the elapsed time since 1970-01-01 00:00:00 */
s = stime(tp);                        /* set the elapsed time start from 1970-01-01 00:00:00 */
s = utime(file, timep);               /* set a file's "last access" time */
s = times(buffer);                    /* get user and system times used so far */
