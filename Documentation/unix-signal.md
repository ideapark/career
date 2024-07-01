```text
---------------------------------------------------------------------------------------
 Name        Value    Default    Source    Meaning
---------------------------------------------------------------------------------------
 SIGHUP      1        Term       POSIX     Hangup
 SIGINT      2        Term       ISO C     Interrupt
 SIGQUIT     3        Core       POSIX     Quit
 SIGILL      4        Core       ISO C     Illegal instruction
 SIGTRAP     5        Core       POSIX     Trace trap
 SIGABRT     6        Core       ISO C     Abort
 SIGIOT      6        Core       BSD       IOT trap
 SIGBUS      7        core       BSD       Bus error
 SIGFPE      8        Core       ISO C     Floating-point exception
 SIGKILL     9        Term       POSIX     Kill, unblockable
 SIGUSR1     10       Term       POSIX     User-defined signal 1
 SIGSEGV     11       Core       ISO C     Segmentation violation
 SIGUSR2     12       Term       POSIX     User-defined signal 2
 SIGPIPE     13       Term       POSIX     Broken pipe
 SIGALRM     14       Term       POSIX     Alarm clock
 SIGTERM     15       Term       ISO C     Termination
 SIGSTKFLT   16       Term       Linux     Stack fault on a processor (unused)
 SIGCHLD     17       Ignr       POSIX     Child process status changed
 SIGCLD      17       Ignr       System V  Same as SIGCHLD (for compatibility only)
 SIGCONT     18                  POSIX     Continue if stopped
 SIGSTOP     19       Stop       POSIX     Stop, unblockable
 SIGTSTP     20       Stop       POSIX     Keyboard stop
 SIGTTIN     21       Stop       POSIX     Background read from tty
 SIGTTOU     22       Stop       POSIX     Background write to tty
 SIGURG      23       Ignr       BSD       Urgent condition on socket
 SIGXCPU     24       Core       BSD       CPU limit exceeded
 SIGXFSZ     25       Core       BSD       File size limit exceeded
 SIGVTALRM   26       Term       BSD       Virtual alarm clock
 SIGPROF     27       Term       BSD       Profiling alarm clock
 SIGWITCH    28       Ignr       BSD       Window size change
 SIGIO       29       Term       BSD       I/O now possible
 SIGPOLL     29       Term       System V  Pollable event occurred: same as SIGIO (for
                                           compatibility only)
 SIGPWR      30       Term       System V  Power failure restart
 SIGSYS      31       Core       POSIX     Bad system call
---------------------------------------------------------------------------------------
    Core: Terminate the process and produce a core file.
    Ignr: Ignore the signal.
    Stop: Stop the process.
    Term: Terminate the process.
---------------------------------------------------------------------------------------
```

# SIGHUP

> Default action: Terminate
> Possible actions: Terminate, Ignore, Function call

SIGHUP is sent by the UART driver to the entire session when a hangup
condition has been detected. Normally, this will kill all the
processes. Some programs, such as `nohup` and `screen`, detach from
their session (and TTY), so that their child processes won't notice a
hangup.

# SIGINT

> Default action: Terminate
> Possible actions: Terminate, Ignore, Function call

SIGINT is sent by the TTY driver to the current foreground job when
the interactive attention character (typically ^C, which has ASCII
code 3) appears in the input stream, unless this behaviour has been
turned off. Anybody with access permissions to the TTY device can
change the interactive attention character and toggle this feature;
additionally, the session manager keeps track of the TTY configuration
of each job, and updates the TTY whenever there is a job switch.

# SIGQUIT

> Default action: Core dump
> Possible actions: Core dump, Ignore, Function call

SIGQUIT works just like SIGINT, but the quit character is typically ^\
and the default action is different.

# SIGPIPE

> Default action: Terminate
> Possible actions: Terminate, Ignore, Function call

The kernel sends SIGPIPE to any process which tries to write to a pipe
with no readers. This is useful, because otherwise jobs like `yes | head`
would never terminate.

# SIGCHLD

> Default action: Ignore
> Possible actions: Ignore, Function call

When a process dies or changes state (stop/continue), the kernel sends
a SIGCHLD to its parent process. The SIGCHLD signal carries additional
information, namely the process id, the user id, the exit status (or
termination signal) of the terminated process and some execution time
statistics. The session leader (shell) keeps track of its jobs using
this signal.

# SIGSTOP

> Default action: Suspend
> Possible actions: Suspend

This signal will unconditionally suspend the recipient, i.e. its
signal action can't be reconfigured. Please note, however, that
SIGSTOP isn't sent by the kernel during job control. Instead, ^Z
typically triggers a SIGTSTP, which can be intercepted by the
application. The application may then e.g. move the cursor to the
bottom of the screen or otherwise put the terminal in a known state,
and subsequently put itself to sleep using SIGSTOP.

# SIGCONT

> Default action: Wake up
> Possible actions: Wake up, Wake up + Function call

SIGCONT will un-suspend a stopped process. It is sent explicitly by
the shell when the user invokes the fg command. Since SIGSTOP can't be
intercepted by an application, an unexpected SIGCONT signal might
indicate that the process was suspended some time ago, and then
un-suspended.

# SIGTSTP

> Default action: Suspend
> Possible actions: Suspend, Ignore, Function call

SIGTSTP works just like SIGINT and SIGQUIT, but the magic character is
typically ^Z and the default action is to suspend the process.

# SIGTTIN

> Default action: Suspend
> Possible actions: Suspend, Ignore, Function call

If a process within a background job tries to read from a TTY device,
the TTY sends a SIGTTIN signal to the entire job. This will normally
suspend the job.

# SIGTTOU

> Default action: Suspend
> Possible actions: Suspend, Ignore, Function call

If a process within a background job tries to write to a TTY device,
the TTY sends a SIGTTOU signal to the entire job. This will normally
suspend the job. It is possible to turn off this feature on a per-TTY
basis.

# SIGWINCH

> Default action: Ignore
> Possible actions: Ignore, Function call

As mentioned, the TTY device keeps track of the terminal size, but
this information needs to be updated manually. Whenever that happens,
the TTY device sends SIGWINCH to the foreground job. Well-behaving
interactive applications, such as editors, react upon this, fetch the
new terminal size from the TTY device and redraw themselves
accordingly.
