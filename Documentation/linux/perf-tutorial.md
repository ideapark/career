# Linux kernel profiling with perf

## Introduction
Perf is a profiler tool for Linux 2.6+ based systems that abstracts away CPU
hardware differences in Linux performance measurements and presents a simple
commandline interface. Perf is based on the perf_events interface exported by
recent versions of the Linux kernel. This article demonstrates the perf tool
through example runs. Output was obtained on

      Operating System: Arch Linux
                Kernel: Linux 3.18.6-1-ARCH
          Architecture: x86-64

running on an Lenovo Thinkpad X230 with dual-core Intel Core i5. For readability,
some output is abbreviated using ellipsis ([...]);

### Commands
The perf tool offers a rich set of commands to collect and analyze performance
and trace data. The command line usage is reminiscent of git in that there is
a generic tool, perf, which implements a set of commands: stat, record, report,
[...]

The list of supported commands:

    $perf --version
    perf version 3.19.0

    $perf

     usage: perf [--version] [--help] [OPTIONS] COMMAND [ARGS]

      The most commonly used perf commands are:
         annotate        Read perf.data (created by perf record) and display annotated code
         archive         Create archive with object files with build-ids found in perf.data file
         bench           General framework for benchmark suites
         buildid-cache   Manage build-id cache.
         buildid-list    List the buildids in a perf.data file
         diff            Read perf.data files and display the differential profile
         evlist          List the event names in a perf.data file
         inject          Filter to augment the events stream with additional information
         kmem            Tool to trace/measure kernel memory(slab) properties
         kvm             Tool to trace/measure kvm guest os
         list            List all symbolic event types
         lock            Analyze lock events
         mem             Profile memory accesses
         record          Run a command and record its profile into perf.data
         report          Read perf.data (created by perf record) and display the profile
         sched           Tool to trace/measure scheduler properties (latencies)
         script          Read perf.data (created by perf record) and display trace output
         stat            Run a command and gather performance counter statistics
         test            Runs sanity tests.
         timechart       Tool to visualize total system behavior during a workload
         top             System profiling tool.
         trace           strace inspired tool
         probe           Define new dynamic tracepoints

      See 'perf help COMMAND' for more information on a specific command.

Certain commands require special support in the kernel and may not be available.
To obtain the list of options for each command, simply type the command name followed
by -h:

    $perf stat -h

     usage: perf stat [<options>] [<command>]

         -T, --transaction     hardware transaction statistics
         -e, --event <event>   event selector. use 'perf list' to list available events
         --filter <filter>     event filter
         -i, --no-inherit      child tasks do not inherit counters
         -p, --pid <pid>       stat events on existing process id
         -t, --tid <tid>       stat events on existing thread id
         -a, --all-cpus        system-wide collection from all CPUs
         -g, --group           put the counters into a counter group
         -c, --scale           scale/normalize counters
         -v, --verbose         be more verbose (show counter open errors, etc)
         -r, --repeat <n>      repeat command and print average + stddev (max: 100, forever: 0)
         -n, --null            null run - dont start any counters
         -d, --detailed        detailed run - start a lot of events
         -S, --sync            call sync() before starting a run
         -B, --big-num         print large numbers with thousands' separators
         -C, --cpu <cpu>       list of cpus to monitor in system-wide
         -A, --no-aggr         disable CPU count aggregation
         -x, --field-separator <separator>
                               print counts with custom separator
         -G, --cgroup <name>   monitor event in cgroup name only
         -o, --output <file>   output file name
             --append          append to the output file
             --log-fd <n>      log output to fd, instead of stderr
             --pre <command>   command to run prior to the measured command
             --post <command>  command to run after to the measured command
         -I, --interval-print <n>
                               print counts at regular interval in ms (>= 100)
             --per-socket      aggregate counts per processor socket
             --per-core        aggregate counts per physical processor core
         -D, --delay <n>       ms to wait before starting measurement after program start

### Events
The perf tool supports a list of measurable events. The tool and underlying kernel
interface can measure events coming from different sources. For instance, some event
are pure kernel counters, in this case they are called *software events*. Examples
include: context-switches, minor-faults.

Another source of events is the processor itself and its Performance Monitoring Unit
(PMU). It provides a list of events to measure micro-architectural events such as
the number of cycles, instructions retired, L1 cache misses and so on. Those events
are called PMU hardware events or hardware events for short. They vary with each
processor type and model.

The perf_events interface also provides a small set of common hardware events monikers.
On each processor, those events get mapped onto an actual events provided by the CPU,
if they exists, otherwise the event cannot be used. Somewhat confusingly, these are
also called *hardware events* and *hardware cache events*.

Finally, there are also *tracepoint events* which are implemented by the kernel ftrace
infrastructure. Those are *only* available with the kernel 2.6.3x and newer kernels.

To obtain a list of supported events:

    $perf list

    List of pre-defined events (to be used in -e):
      cpu-cycles OR cycles                               [Hardware event]
      instructions                                       [Hardware event]
      cache-references                                   [Hardware event]
      cache-misses                                       [Hardware event]
      branch-instructions OR branches                    [Hardware event]
      branch-misses                                      [Hardware event]
      bus-cycles                                         [Hardware event]
      stalled-cycles-frontend OR idle-cycles-frontend    [Hardware event]
      ref-cycles                                         [Hardware event]

      cpu-clock                                          [Software event]
      task-clock                                         [Software event]
      page-faults OR faults                              [Software event]
      context-switches OR cs                             [Software event]
      cpu-migrations OR migrations                       [Software event]
      minor-faults                                       [Software event]
      major-faults                                       [Software event]
      alignment-faults                                   [Software event]
      emulation-faults                                   [Software event]
      dummy                                              [Software event]

      L1-dcache-load-misses                              [Hardware cache event]
      L1-dcache-store-misses                             [Hardware cache event]
      L1-dcache-prefetch-misses                          [Hardware cache event]
      L1-icache-load-misses                              [Hardware cache event]
      LLC-loads                                          [Hardware cache event]
      LLC-stores                                         [Hardware cache event]
      LLC-prefetches                                     [Hardware cache event]
      dTLB-load-misses                                   [Hardware cache event]
      dTLB-store-misses                                  [Hardware cache event]
      iTLB-loads                                         [Hardware cache event]
      iTLB-load-misses                                   [Hardware cache event]
      branch-loads                                       [Hardware cache event]
      branch-load-misses                                 [Hardware cache event]


      branch-instructions OR cpu/branch-instructions/    [Kernel PMU event]
      branch-misses OR cpu/branch-misses/                [Kernel PMU event]
      bus-cycles OR cpu/bus-cycles/                      [Kernel PMU event]
      cache-misses OR cpu/cache-misses/                  [Kernel PMU event]
      cache-references OR cpu/cache-references/          [Kernel PMU event]
      cpu-cycles OR cpu/cpu-cycles/                      [Kernel PMU event]
      instructions OR cpu/instructions/                  [Kernel PMU event]
      mem-loads OR cpu/mem-loads/                        [Kernel PMU event]
      mem-stores OR cpu/mem-stores/                      [Kernel PMU event]
      power/energy-cores/                                [Kernel PMU event]
      power/energy-gpu/                                  [Kernel PMU event]
      power/energy-pkg/                                  [Kernel PMU event]
      stalled-cycles-frontend OR cpu/stalled-cycles-frontend/ [Kernel PMU event]
      uncore_cbox_0/clockticks/                          [Kernel PMU event]
      uncore_cbox_1/clockticks/                          [Kernel PMU event]
      uncore_imc/data_reads/                             [Kernel PMU event]
      uncore_imc/data_writes/                            [Kernel PMU event]

      rNNN                                               [Raw hardware event descriptor]
      cpu/t1=v1[,t2=v2,t3 ...]/modifier                  [Raw hardware event descriptor]
             (see 'man perf-list' on how to encode it)

      mem:<addr>[:access]                                [Hardware breakpoint]

      kvmmmu:kvm_mmu_pagetable_walk                      [Tracepoint event]
      kvmmmu:kvm_mmu_paging_element                      [Tracepoint event]
      kvmmmu:kvm_mmu_set_accessed_bit                    [Tracepoint event]
      kvmmmu:kvm_mmu_set_dirty_bit                       [Tracepoint event]
      kvmmmu:kvm_mmu_walker_error                        [Tracepoint event]
      kvmmmu:kvm_mmu_get_page                            [Tracepoint event]
      kvmmmu:kvm_mmu_sync_page                           [Tracepoint event]
      kvmmmu:kvm_mmu_unsync_page                         [Tracepoint event]
      [...]

An event can have sub-events (or unit masks). On some processors and for some events,
it may be possible to combine unit masks and measure when either sub-event occurs.
Finally, an event can have modifiers, i.e., filters which alter when or how the event
is counted.

#### Hardware events
PMU hardware events are CPU specific and documented by the CPU vendor. The perf
tool, if linked against the libpfm4 library, provides some short description of
the events. For a listing of PMU hardware events for Intel and AMD processors,
see

- Intel PMU event tables [here](http://www.intel.com/Assets/PDF/manual/253669.pdf):
- AMD PMU event table [here](http://support.amd.com/us/Processor_TechDocs/31116.pdf):

## Counting with perf stat
For any of the supported events, perf can keep a running count during process
execution. In counting modes, the occurrences of events are simply aggregated
and presented on standard output at the end of an application run. To generate
these statistics, use the stat command of perf. For instance:

    $perf stat -B dd if=/dev/zero of=/dev/null count=1000000
    1000000+0 records in
    1000000+0 records out
    512000000 bytes (512 MB) copied, 0.37408 s, 1.4 GB/s

     Performance counter stats for 'dd if=/dev/zero of=/dev/null count=1000000':

             375.296760      task-clock (msec)         #    0.884 CPUs utilized
                      6      context-switches          #    0.016 K/sec
                      0      cpu-migrations            #    0.000 K/sec
                     57      page-faults               #    0.152 K/sec
              960858335      cycles                    #    2.560 GHz
              369238206      stalled-cycles-frontend   #   38.43% frontend cycles idle
                      0      stalled-cycles-backend    #    0.00% backend  cycles idle
             1614188040      instructions              #    1.68  insns per cycle
                                                       #    0.23  stalled cycles per insn
              313228532      branches                  #  834.616 M/sec
                1010559      branch-misses             #    0.32% of all branches

            0.424510661 seconds time elapsed

With no events specified, perf stat collects the common events listed above. Some
are software events, such as context-switches, others are generic hardware events
such as cycles. After the hash sign, derived metrics may be presented, such as 'IPC'
(instructions per cycle).

### Options controlling event selection
It is possible to measure one or more events per run of the perf tool. Events are
designated using their symbolic names followed by optional unit masks and modifiers.
Event names, unit masks, and modifiers are case insensitive.

By default, events are measured at *both* user and kernel levels:

    $perf stat -e cycles dd if=/dev/zero of=/dev/null count=100000

To measure only at the user level, it is necessary to pass a modifier:

    $perf stat -e cycles:u dd if=/dev/zero of=/dev/null count=100000

To measure both user and kernel (explicitly):

    $perf stat -e cycles:uk dd if=/dev/zero of=/dev/null count=100000

#### Modifiers
Events can optionally have a modifier by appending a colon and one or more modifiers.
Modifiers allow the user to restrict when events are counted.

To measure a PMU event and pass modifiers:

    $perf stat -e instructions:u dd if=/dev/zero of=/dev/null count=100000

In this example, we are measuring the number of instructions at the user level.
Note that for actual events, the modifiers depends on the underlying PMU model.
All modifiers can be combined at will. Here is a simple table to summarize the
most common modifiers for Intel and AMD x86 processors.

    | Modifiers |                         Description                       | Example |
    |---------------------------------------------------------------------------------|
    | u         | monitor at priv level 3,2,1 (user)                        | event:u |
    | k         | monitor at priv level 0 (kernel)                          | event:k |
    | h         | monitor hypervisor events on a virtualization environment | event:h |
    | H         | monitor host machine on a virtualization environment      | event:H |
    | G         | monitor guest machine on a virtualization environment     | event:G |

All modifiers above are considered as a boolean (flag).

#### Hardware events
To measure an actual PMU as provided by the HW vendor documentation, pass the hexadecimal
parameter code:

    $perf stat -e r1a8 -a sleep 1

     Performance counter stats for 'system wide':

                 126482      r1a8

            1.001279657 seconds time elapsed

#### multiple events
To measure more than one event, simply provide a comma-separated list with no
space:

    $perf stat -e cycles,instructions,cache-miss [...]

There is no theoretical limit in terms of the number of events that can be
provided. If there are more than there are actual hw counters, the kernel will
automatically multiplex them. There is no limit of the number of software events.
It is possible to simultaneously measure events coming from different sources.
However, given that there is one file descriptor used per event and either
per-thread (per-thread mode) or per-cpu (system-wide), it is possible to reach
the maximum number of open file descriptor per process as imposed by the kernel.
In that case, perf will report an error. See the troubleshooting section for
help with this matter.

#### multiplexing and scaling events
If there are more events than counters, the kernel uses time multiplexing (switch
frequency = HZ, generally 100 or 1000) to give each event a chance to access the
monitoring hardware. Multiplexing only applies to PMU events. With multiplexing,
an event is *not* measured all the time. At the end of the run, the tool *scales*
the count based on total time enabled vs time running. The actual formula is:

    file_count = raw_count * time_enabled/time_running

This provides an *estimate* of what the count would have been, had the event been
measured during the entire run. It is *very* important to understand this is an
*estimate* not an actual count. Depending on the workload, there will be blind
spots which can introduce errors during scaling.

Events are currently managed in round-robin fashion. Therefore each event will
eventually get a chance to run. If there are N counters, then up to the first N
events on the round-robin list are programmed into the PMU. In cretain situations
it may be less than that because some events may not be measured together or they
compete for the same counter. Futhermore, the perf_events interface allows multiple
tools to measure the same thread or CPU at the same time. Each event is added to
the same round-robin list. There is no guarantee that all events of a tool are
stored sequentially in the list.

To avoid scaling (in the presence of only one active perf_event user), one can try
and reduce the number of events. The following table provides the number of
counters for a few common processor:

    |   Processor   | Generic counters | Fixed counters |
    |---------------------------------------------------|
    | Intel Core    | 2                | 3              |
    | Intel Nehalem | 4                | 3              |

Generic counters can measure any events. Fixed counters can only measure one event.
Some counters may be reserved for special purposes, such as a watchdog timer, The
following examples show the effect of scaling:

    $perf stat -B -e cycles,cycles ls -R ~ > /dev/null

     Performance counter stats for 'ls -R /home/thinpark/':

              157645520      cycles
              157645520      cycles

            0.096576280 seconds time elapsed

Here, there is no multiplexing and thus no scaling. Let's add one more event:

    $perf stat -B -e cycles,cycles,cycles,cycles,cycles ls -R ~ > /dev/null

     Performance counter stats for 'ls -R /home/thinpark/':

              157150443      cycles                    [78.39%]
              155643261      cycles                    [81.24%]
              157402362      cycles                    [81.52%]
              156922424      cycles                    [81.43%]
              157577430      cycles                    [78.35%]

            0.097612663 seconds time elapsed

There was multiplexing and thus scaling. It can be interesting to try and pack events
in a way that guarantees that event A and B are always measured together. Although
the perf_events kernel interface provides support for event grouping, the current perf
tool does *not*.

#### Repeated measurement
It is possible to use perf stat to run the same test workload multiple times
and get for each count, the standard deviation from the mean.

    $perf stat -r 5 sleep 1

     Performance counter stats for 'sleep 1' (5 runs):

               0.697678      task-clock (msec)         #    0.001 CPUs utilized            ( +-  3.75% )
                      1      context-switches          #    0.001 M/sec
                      0      cpu-migrations            #    0.000 K/sec
                     48      page-faults               #    0.069 M/sec                    ( +-  0.51% )
                 828450      cycles                    #    1.187 GHz                      ( +-  2.91% )
                 546854      stalled-cycles-frontend   #   66.01% frontend cycles idle     ( +-  3.99% )
                      0      stalled-cycles-backend    #    0.00% backend  cycles idle
                 599389      instructions              #    0.72  insns per cycle
                                                       #    0.91  stalled cycles per insn  ( +-  0.95% )
                 121176      branches                  #  173.685 M/sec                    ( +-  0.86% )
                   6879      branch-misses             #    5.68% of all branches          ( +-  1.01% )

            1.001356513 seconds time elapsed                                          ( +-  0.01% )

Here, sleep is run 5 times and the mean count for each event, along with ratio of
std-dev/mean is printed.

### Options controlling environment selection
The perf tool can be used to count events on a per-thread, per-process, per-cpu
or system-wide basis. In per-thread mode, the counter only monitors the execution
of a designated thread. When the thread is scheduled out, monitoring stops. When
a thread migrated from one processor to another, counters are saved on the current
processor and are restored on the new one.

The per-process mode is variant of per-thread where all threads of the process are
monitored. Counts and samples are aggregated at the process level. The perf_events
interface allows for automatic inheritance on fork() and pthread_create(). By
default, the perf tool *activates* inheritance.

In per-cpu mode, all threads running on the designated processors are monitored.
Counts and samples are thus aggregated per CPU. An event is only monitoring one
CPU at a time. To monitor across multiple processors, it is necessary to create
multiple events. The perf tool can aggregate counts and samples across multiple
processors. It can also monitor only a subset of the processors.

#### Counting and inheritance
By default, perf stat counts for all threads of the process and subsequent child
processes and threads. This can be altered using the -i option. It is not possible
to obtain a count breakdown per-thread or per-process.

#### Processor-wide mode
By default, perf stat counts in per-thread mode. To count on per-cpu basis pass
the -a option. When it is specified by itself, all online processors are monitored
and counts are aggregated. For instance:

    $perf stat -B -e cycles:u,instructions:u -a dd if=/dev/zero of=/dev/null count=2000000
    2000000+0 records in
    2000000+0 records out
    1024000000 bytes (1.0 GB) copied, 0.697352 s, 1.5 GB/s

     Performance counter stats for 'system wide':

              475329299      cycles:u                  [100.00%]
              682884270      instructions:u            #    1.44  insns per cycle

            0.698479870 seconds time elapsed

This measurement collects events cycles and instructions across all CPUs. The duration
of the measurement is determined by the execution of dd. In other words, this measurement
captures execution of the dd process *and* anything else than runs at the user level on
all CPUs.

To time the duration of the measurement without actively consuming cycles, it is possible
to use the =/usr/bin/sleep= command:

    $perf stat -B -e cycles:u,instructions:u -a sleep 5

     Performance counter stats for 'system wide':

               42771933      cycles:u                  [100.00%]
                6426054      instructions:u            #    0.15  insns per cycle

            5.001319860 seconds time elapsed

It is possible to restrict monitoring to a subset of the CPUs using the -C option.
A list of CPUs to monitor can be passed. For instance, to measure on CPU0, CPU2
and CPU3:

    $perf stat -B -e cycles:u,instructions:u -a -C 0,2-3 sleep 5

The demonstration machine has only two CPUs, but we can limit to CPU 1.

    $perf stat -B -e cycles:u,instructions:u -a -C 1 sleep 5

     Performance counter stats for 'system wide':

               29227302      cycles:u                  [100.00%]
                6072616      instructions:u            #    0.21  insns per cycle

            5.001221140 seconds time elapsed

Counts are aggregated across all the monitored CPUs. Notice how the number of counted
cycles and instructions are both halved when measuring a single CPU.

#### Attaching to a running process
It is possible to use perf to attach to an already running thread or process. This
requires the permission to attach along with the thread or process ID. To attach
to a process, the -p option must be the process ID. To attach to the systemd service
that is commonly running on Arch Linux machines, issue:

    $perf stat -e cycles -p $(pidof systemd) sleep 2

     Performance counter stats for process id '454':

          <not counted>      cycles

            2.001316296 seconds time elapsed

What determines the duration of the measurement is the command to execute. Even though
we are attaching to a process, we can still pass the name of a command. It is used to
time the measurement. Without it, perf monitors until it is killed. Also note that when
attaching to a process, all threads of the process are monitored. Futhermore, given that
inheritance is on by default, child processes or threads will also be monitored. To turn
this off, you must use the -i option. It is possible to attach a specific thread within
a process. By thread, we mean kernel visible thread. In other words, a thread visible
by the ps or top commands. To attach to a thread, the -t option must be used. We look at
systemd, because it always runs on Arch Linux, with multiple threads.

    $ps -L ax | fgrep systemd | head -5

      138   138 ?        Ss     0:03 /usr/lib/systemd/systemd-journald
      182   182 ?        Ss     0:00 /usr/lib/systemd/systemd-udevd
      292   292 ?        Ssl    0:00 /usr/lib/systemd/systemd-timesyncd
      292   296 ?        Ssl    0:00 /usr/lib/systemd/systemd-timesyncd
      292 18020 ?        Ssl    0:00 /usr/lib/systemd/systemd-timesyncd

    $perf stat -e cycles -t 138 sleep 2

     Performance counter stats for thread id '138':

          <not counted>      cycles

            2.001321991 seconds time elapsed

In this example, the thread 138 did not run during the 2s of the measurement. Otherwise,
we would see a count value. Attaching to kernel threads is possible, though not really
recommanded. Given that kernel threads tend to be pinned to a specific CPU, it is best
to use the cpu-wide mode.

### Options controlling output
perf stat can modify output to suit different needs.

#### Pretty printing large numbers
For most people, it is hard to read large numbers. With perf stat, it is possible to
print large numbers using the comma separator for thousands (US-style). For that the
-B option and the correct locale for LC_NUMERIC must be set. As the above example
showed, My Arch Linux already sets the locale information correctly. An explicit call
looks as follows:

    $LC_NUMERIC=en_US.UTF8 perf stat -B -e cycles:u,instructions:u dd if=/dev/zero of=/dev/null count=1000000
     Performance counter stats for 'dd if=/dev/zero of=/dev/null count=1000000':

              227,047,142      cycles:u
              340,283,829      instructions:u            #    1.50  insns per cycle

            0.375279431 seconds time elapsed

#### Machine readable output
perf stat can also print counts in a format that can easily be imported into a
spreadsheet or parsed by scripts. The -x option alters the format of the output
and allows users to pass a field delimiter. This makes it easy to produce CSV-style
output:

    $perf stat -x, date
    Sun Mar  8 20:11:54 CST 2015
    0.773558,,task-clock
    1,,context-switches
    0,,cpu-migrations
    50,,page-faults
    988930,,cycles
    663559,,stalled-cycles-frontend
    0,,stalled-cycles-backend
    687097,,instructions
    139049,,branches
    9020,,branch-misses

Note that the -x option is not compatible with -B.

## Sampling with perf record
The perf tool can be used to collect profiles on per-thread, per-process and per-cpu
basis.

There are several commands associated with sampling: record, report, annotate. You
must first collect the samples using perf record. This generates an output file called
perf.data. That file can then be analyzed, possibly on another machine, using the perf
report annotate commands. The model is fairly similar to that of OProfile.

### Event-based sampling overview
Perf_events is based on event-based sampling. The period is expressed as the number of
occurrences of an event, not the number of timer ticks. A sample is recorded when the
sampling counter overflows, i.e., wraps from 2^64 back to 0. No PMU implements 64-bit
hardware counters, but perf_events emulates such counters in software.

The way perf_events emulates 64-bit counter is limited to expressing sampling periods
using the number of bits in the actual hardware counters. It this is smaller than 64,
the kernel *silently* truncates the period in this case. Therefore, it is best if the
period is always smaller than 2^31 if running on 32-bit systems.

On counter overflow, the kernel records infromation, i.e., a sample, about the execution
of the program. What gets recorded depends on the type of measurement. This is all
specified by the user and the tool. But the key information that is common in all samples
is the instruction pointer, i.e. Where was the program when is was interrupted.

Interrupt-based sampling introduces skids on modern processors. That means that the
instruction pointer stored in each sample designates the place where the program was
interrupted to process the PMU interrupt, not the place where the counter actually
overflows, i.e., where it was at the end of the sampling period. In some case, the
distance between those two points may be severval dozen instructions or more if there
were taken branches. When the program cannot make forward progress, those two locations
are indeed identical. For this reason, care must be taken when interpreting profiles.

#### Default event: cycle counting
By default, perf record uses the cycles event as the sampling event. This is a generic
hardware event that is mapped to a hardware-specific PMU event by the kernel. For Intel,
it is mapped to UNHALTED_CORE_CYCLES. This event does not maintain a constant correlation
to time in the presence of CPU frequency scaling. Intel provides another event, called
UNHALTED_REFERENCE_CYCLES but this event is NOT currently available with perf_events.

On AMD systems, the event is mapped to CPU_CLK_UNHALTED and this event is also subject
to frequency scaling. On any Intel or AMD precessor, the cycle event does not count
when the process is idle, i.e., when it calls mwait().

#### Period and rate
The perf_events interface allows two modes to express the sampling period:

- the number of occurrences of the event (period)
- the average rate of samples/sec (frequency)

The perf tool defaults to the average rate. It is set to 1000Hz, or 1000 samples/sec.
That means that the kernel is dynamically adjusting the sampling period to achieve
the target average rate. The adjustment in period is reported in the raw profile data.
In contrast, with the other mode, the sampling period is set by the user and does not
vary between samples. There is currently no support for sampling period randomization.

### Collecting samples
By default, perf record operates in per-thread mode, with inherit mode enabled. The
simplest mode looks as follows, when executing a simple program that busy loops:

    $perf record ls -R ~ > /dev/null
    [ perf record: Woken up 1 times to write data ]
    [ perf record: Captured and wrote 0.028 MB perf.data (~1222 samples) ]

The example above collects samples for event cycles at an average target rate of 1000Hz.
The resulting samples are saved into the perf.data file. If the file already existed,
you may be prompted to pass -f to overwrite it. To put the results in a specific file,
use the -o option.

WARNING: The number of reported samples is only an estimate. It does not reflect the
actual number of samples collected. The estimate is based on the number of bytes
written to the perf.data file and the minimal sample size. But the size of each sample
depends on the type of measurement. Some samples are generated by the counters themselves
but others are recorded to support symbol correlation during post-processing, e.g.,
mmap() information.

To get an accurate number of samples for the perf.data file, it is possible to use the
perf report command:

    $perf report -D -i perf.data | fgrep RECORD_SAMPLE | wc -l
    373

To specify a custom rate, it is necessary to use the -F option. For instance, to sample
on event instructions only at the user level and at an average rate of 250 samples/sec:

    $perf record -e instructions:u -F 250 ls -R ~ > /dev/null
    [ perf record: Woken up 1 times to write data ]
    [ perf record: Captured and wrote 0.015 MB perf.data (~654 samples) ]

To specify a sampling period, instead, the -c option must be used. For instance, to
collect a sample every 2000 occurrences of event instructions only at the user level
only:

    $perf record -e retired_instructions:u -c 2000 ls -R ~ > /dev/null
    [ perf record: Woken up 55 times to write data ]
    [ perf record: Captured and wrote 13.514 MB perf.data (~590431 samples) ]

### Processor-wide mode
In per-cpu mode mode, samples are collected for all threads executing on the monitored
CPU. To switch perf record in per-cpu mode, the -a option must be used. By default in
this mode, *ALL* online CPUs are monitored. It is possible to restrict to a subset of
CPUs using the -C option, as explained with perf stat above.

To sample on cycles at both user and kernel levels for 5s on all CPUs with an average
target rate of 1000 samples/sec:

    $perf record -a -F 1000 sleep 5
    [ perf record: Woken up 1 times to write data ]
    [ perf record: Captured and wrote 0.334 MB perf.data (~14608 samples) ]

## Sample analysis with perf report
Samples collected by perf record are saved into a binary file called, by default,
perf.data. The perf report command reads this file and generates a concise execution
profile. By default, samples are sorted by functions with the most samples first.
It is possible to customize the sorting order and therefore to view the data
differently.

    $perf report --stdio
    # To display the perf.data header info, please use --header/--header-only options.
    #
    # Samples: 51  of event 'cycles'
    # Event count (approx.): 181148060
    #
    # Overhead  Command          Shared Object            Symbol
    # ........  ...............  .......................  ............................
    #
        13.58%  plugin-containe  [kernel.vmlinux]         [k] system_call
        12.09%  swapper          [kernel.vmlinux]         [k] intel_pstate_timer_func
        11.20%  swapper          [kernel.vmlinux]         [k] get_next_timer_interrupt
         8.93%  perf             [kernel.vmlinux]         [k] vma_interval_tree_remove
         8.27%  swapper          [kernel.vmlinux]         [k] call_timer_fn
         6.41%  swapper          [rtl_pci]                [k] pci_read32_sync
         5.22%  kworker/u16:0    [kernel.vmlinux]         [k] _cond_resched
         4.25%  plugin-containe  [kernel.vmlinux]         [k] _raw_spin_lock_irqsave
         3.07%  plugin-containe  libpthread-2.21.so       [.] pthread_getspecific
         2.68%  plugin-containe  [kernel.vmlinux]         [k] eventfd_poll
         2.50%  plugin-containe  libflashplayer.so        [.] 0x00000000007f5cba
         2.50%  swapper          [kernel.vmlinux]         [k] __switch_to
         2.25%  swapper          [kernel.vmlinux]         [k] intel_idle
         [...]

The column 'Overhead' indicates the percentage of the overall samples collected in
the corresponding function. The second column reports the process from which the
samples were collected. In per-thread/per-process mode, this is always the same of
the monitored command. But in cpu-wide mode, the command can vary. The third column
shows the name of the ELF image where the samples came from. If a program is dynamically
linked, then this may show the name of a shared library. When the samples come from
the kernel, then the pseudo ELF image name [kernel.kallsyms] is used. The fourth
column indicates the privilege level at which the sample was taken, i.e. when the
program was running when it was interrupted:

- [.]: user level
- [k]: kernel level
- [g]: guest kernel level (virtualization)
- [u]: guest os user space
- [H]: hypervisor

The final column shows the symbol name.

There are many different ways samples can be presented, i.e., sorted. To sort by shared
objects, i.e., dsos:

    $perf report --sort=dso --stdio

### Options controlling output
To make the output easier to parse, it is possible to change the column separator
to a single character:

    $perf report -t

### Options controlling kernel reporting
The perf tool does not know how to extract symbols form compressed kernel images
(vmlinuz). Therefore, users must pass the path of the uncompressed kernel using
the -k option:

    $perf report -k /tmp/vmlinux

Of course, this works only if the kernel is compiled with debug symbols.

### Processor-wide mode
In per-cpu mode, samples are recorded from all threads running on the monitored CPUs.
As a result, samples from many different processes may be collected. For instance,
if we monitor across all CPUs for 5s:

    $perf record -a sleep 5
    $perf report
    # To display the perf.data header info, please use --header/--header-only options.
    #
    # Samples: 819  of event 'cycles'
    # Event count (approx.): 248205111
    #
    # Overhead  Command          Shared Object                Symbol
    # ........  ...............  ...........................  ............................................
    #
        10.26%  swapper          [kernel.vmlinux]             [k] intel_idle
         1.88%  swapper          [rtl_pci]                    [k] pci_read32_sync
         1.29%  swapper          [i8042]                      [k] i8042_interrupt
         1.06%  plugin-containe  [kernel.vmlinux]             [k] do_sys_poll
         0.91%  swapper          [kernel.vmlinux]             [k] __switch_to
         0.85%  kworker/1:2      [kernel.vmlinux]             [k] delay_tsc
         0.82%  plugin-containe  libglib-2.0.so.0.4200.2      [.] g_mutex_lock
         0.80%  perf             [kernel.vmlinux]             [k] find_vma
         0.76%  kworker/1:2      [kernel.vmlinux]             [k] native_read_tsc
         0.74%  xfsettingsd      libpthread-2.21.so           [.] __errno_location
         0.73%  kworker/1:2      [rtl_pci]                    [k] pci_read32_sync
         0.70%  perf             [kernel.vmlinux]             [k] select_task_rq_fair
         0.70%  swapper          [kernel.vmlinux]             [k] cpuidle_enter_state
         0.59%  swapper          [kernel.vmlinux]             [k] menu_select
         [...]

When the symbol is printed as an hexadecimal address, this is because the ELF image
does not have a symbol table. This happens binaries are stripped. We can sort by cpu
as well. This would be useful to determine if the workload is well balanced:

    $perf report --sort=cpu

    # Events: 354  cycles
    #
    # Overhead  CPU
    # ........  ...
    #
       65.85%  1
       34.15%  0

## Source level analysis with perf annotate
It is possible to drill down to the instruction level with perf annotate. For that,
you need to invoke perf annotate with the name of the command to annotate. All the
functions with samples will be disassembled and each instruction will have its
relative percentage of samples reported:

    $perf record ls -R ~ > /dev/null
    $perf annotate -d $(which ls) --stdio
     Percent |      Source code & Disassembly of ls for cycles
     ----------------------------------------------------------
             :
             :
             :
             :      Disassembly of section .plt:
             :
             :      0000000000402250 <__errno_location@plt>:
      100.00 :        402250:       jmpq   *0x219e12(%rip)        # 61c068 <_fini+0x209dec>
        0.00 :        402256:       pushq  $0xa
        0.00 :        40225b:       jmpq   4021a0 <_init+0x20>
     Percent |      Source code & Disassembly of ls for cycles
    ----------------------------------------------------------
             :
             :
             :
             :      Disassembly of section .plt:
             :
             :      0000000000402210 <free@plt>:
      100.00 :        402210:       jmpq   *0x219e32(%rip)        # 61c048 <_fini+0x209dcc>
        0.00 :        402216:       pushq  $0x6
        0.00 :        40221b:       jmpq   4021a0 <_init+0x20>
     Percent |      Source code & Disassembly of ls for cycles
    ----------------------------------------------------------
             :
             :
             :
             :      Disassembly of section .plt:
             :
             :      0000000000402630 <malloc@plt>:
      100.00 :        402630:       jmpq   *0x219c22(%rip)        # 61c258 <_fini+0x209fdc>
        0.00 :        402636:       pushq  $0x48
        0.00 :        40263b:       jmpq   4021a0 <_init+0x20>

The first column reports the percentage of samples for function ==malloc()== captured
for at that instruction. As explained earlier, you should interpret this information
carefully.

perf annotate can generate sourcedoe level information if the application is compiled
with -ggdb.

### Using perf annotate on kernel code
The perf tool does not know how to extract symbols from compressed kernel images (vmlinuz).
As in the case of perf report, users must pass the path of the uncompressed kernel using
the -k option:

    $perf annotate -k /tmp/vmlinux -d symbol

Again, this only works if the kernel is compiled to with debug symbols.

## Live analysis with perf top
The perf tool can operate in a mode similar to the Linux top tool, printing sampled
functions in real time. The default sampling event is cycles and default order is
descending number of samples per symbol, thus perf top shows the functions where
most of the time spent. By default, perf top operates in processor-wide mode,
monitoring all online CPUs at both user and kernel levels. It is possible to monitor
only a subset of the CPUs using the -C option.

    $perf top

       PerfTop:      79 irqs/sec  kernel:91.1%  exact:  0.0% [4000Hz cycles],  (all, 4 CPUs)
       -------------------------------------------------------------------------------

           15.87%  [rtl_pci]         [k] 0x000000000000004f
            4.16%  [kernel]          [k] native_read_tsc
            4.12%  perf              [.] symbols__insert
            3.68%  [kernel]          [k] delay_tsc
            2.11%  perf              [.] symbol_filter
            2.02%  perf              [.] rb_next
            1.65%  perf              [.] rb_insert_color
            1.57%  libc-2.21.so      [.] strlen
            1.56%  perf              [.] internal_cplus_demangle
            1.47%  perf              [.] dso__load_sym
            1.38%  [kernel]          [k] menu_select
            1.31%  libc-2.21.so      [.] __strcmp_sse2_unaligned
            1.25%  libc-2.21.so      [.] vfprintf
            1.15%  [i915]            [k] 0x000000000004e847
            1.05%  libc-2.21.so      [.] _int_malloc
            0.79%  [kernel]          [k] get_page_from_freelist
            0.76%  [kernel]          [k] rcu_try_advance_all_cbs
            0.71%  libc-2.21.so      [.] __libc_calloc
            0.71%  libelf-0.161.so   [.] gelf_getsym
            0.65%  [kernel]          [k] get_next_timer_interrupt

Press 'h' for more command such as drill down the function assembly code.

## Benchmarking with perf bench
The perf bench command includes a number of multi-threaded microbenchmarks to execrise
different subsystems in the Linux kernel and system calls. This allows hackers to
easily stress and measure the impact of changes, and therefore help mitigate performance
regressions.

It also serves as a general bechmark framework, enabling developers to easily create
test cases and transparently integrate and make use of the rich perf tool subsystem.

### sched: Scheduler benchmarks
Measure pipe(2) and socketpair(2) operations between multiple tasks. Allows the
measurement of thread versus process context switch performance.

    $perf bench sched messaging -g 64
    # Running 'sched/messaging' benchmark:
    # 20 sender and receiver processes per group
    # 64 groups == 2560 processes run

         Total time: 1.451 [sec]

### mem: Memory access benchmarks

### numa: NUMA scheduling and MM benchmarks

### futex: Futex stressing benchmarks
Deals with finer grained aspects of the kernel's implementation of futexes. It is
mostly userful for kernel hacking. It currently supports wakeup and requeue/wait
operations, as well as stressing the hashing scheme for both private and shared
futexes. An example run for nCPU threads, each handling 1024 futexes measuring the
hashing logic:

    $perf bench futex hash
    # Running 'futex/hash' benchmark:
    Run summary [PID 6280]: 4 threads, each operating on 1024 [private] futexes for 10 secs.

    [thread  0] futexes: 0x10f1b50 ... 0x10f2b4c [ 4654387 ops/sec ]
    [thread  1] futexes: 0x10f2b60 ... 0x10f3b5c [ 4718489 ops/sec ]
    [thread  2] futexes: 0x10f3b70 ... 0x10f4b6c [ 4272947 ops/sec ]
    [thread  3] futexes: 0x10f4d00 ... 0x10f5cfc [ 4784640 ops/sec ]

    Averaged 4607615 operations/sec (+- 2.49%), total secs = 10

## Troubleshooting and Tips
This section lists a number of tips to avoid common pitfalls when using perf.

### Open file limits
The design of the perf_events kernel interface which is used by the perf tool, is such
that it uses one file descriptor per event per-thread or per-cpu.

On a 16-way system, when you do:

    $perf stat -e cycles sleep 1

You are effectively creating 16 events, and thus consuming 16 file descriptors.

In per-thread mode, when you are sampling a processing with 100 threads on the
same 16-way system:

    $perf record -e cycles my_hundred_thread_process

Then, once call the threads are created, you end up with

    100 * 1 (event) * 16 (cpus) = 1600

file descriptors. Perf creates one instance of the event on each CPU. Only when
the thread executes on that CPU does the event effectively measure. This approach
enforces sampling buffer locality and thus mitigates sampling overhead. At the
end of the run, the tool aggregates all the samples into a single output file.

In case perf aborts with 'too many open files' error, there are a few solutions:

- increase the number of per-process open files using ulimit -n. Caveat: you must be root
- limit the number of events you measure in one run
- limit the number of CPU you are measuring

#### increasing open file limit
The superuser can override the per-process open file limit using the ulimit shell
builtin command:

    core file size          (blocks, -c) 0
    data seg size           (kbytes, -d) unlimited
    scheduling priority             (-e) 20
    file size               (blocks, -f) unlimited
    pending signals                 (-i) 6756
    max locked memory       (kbytes, -l) 64
    max memory size         (kbytes, -m) unlimited
    open files                      (-n) 1024
    pipe size            (512 bytes, -p) 8
    POSIX message queues     (bytes, -q) 819200
    real-time priority              (-r) 0
    stack size              (kbytes, -s) 8192
    cpu time               (seconds, -t) unlimited
    max user processes              (-u) 6756
    virtual memory          (kbytes, -v) unlimited
    file locks                      (-x) unlimited

### Binary identification with build-id
The perf record command saves in the perf.data unique identifiers for all ELF images
relevant to the measurement. In per-thread mode, this includes all the ELF images of
the monitored process. In cpu-wide mode, it includes all running processes running on
the system. Those unique identifiers are generated by the linker if the -WL, --build-id
option is used. thus they are called build-id. The build-id are helpfull tool when
correlating instruction addresses to ELF images. To extract all build-id entries used
in a perf.data file, issue:

    $perf buildid-list -i perf.data
    6ebcee76c4b04895598b4df86ec445c49fc137a2 /lib/modules/3.18.6-1-ARCH/build/vmlinux
    0dc7c4fce016ac5209af8f4ea09a1298bbfb1596 /lib/modules/3.18.6-1-ARCH/kernel/fs/ext4/ext4.ko.gz
    57903992ced692cb58bae0a819430d550a3b0412 /usr/bin/ls
    9ac81172d5ff96f40d984fe7c10073a98f1a6b2e /usr/lib/libc-2.21.so

#### The build-id cache
At the end of each run, the perf record command updates a build-id cache, with new
entries for ELF images with samples. The cache contains:

- build-id for ELF images with samples
- copies of the ELF images with samples

Given that build-id are immutable, they uniquely identify a binary. If a binary is
recompiled, a new build-id is generated and a new copy of the ELF images is saved in
the cache. The cache is saved on disk in a directory which is by default $HOME/.debug.
There is a global configuration file ==/etc/perfconfig== which can be used by sysadmin
to specify an alternate global directory for the cache:

    $cat /etc/perfconfig
    [buildid]
    dir = /var/tmp/.debug

In certain situations it may be beneficial to turn off the build-id cache updates
altogether. For that, you must pass the -N option to perf record

    $perf record -N dd if=/dev/zero of=/dev/null count=100000

### Access Control
For some events, it is necessary to be root invoke the perf tool. This document assumes
that the user has root privileges. If you try to run perf with insufficient privileges,
it will report

    No permission to collect system-wide stats.

## Other Scenarios

### Profiling sleep times
This feature shows where and how long a program is sleeping or waiting something.

The first step is collecting data. We need to collect sched_stat and sched_switch
events. Sched_stat events are not enough, because they are generated in the context
of a task, which wakes up a target task (e.g. releases a lock). We need the same event
but with a call-chain of the target task. This call-chain can be extracted from a
previous sched_switch event.

The second step is merging sched_start and sched_switch events. It can be done with
help of "perf inject -s".

    $perf record -e sched:sched_stat_sleep,sched:sched_switch,sched:sched_process_exit -g -o /tmp/perf.data.raw /bin/ls
    $perf inject -v -s -i /tmp/perf.data.raw -o /tmp/perf.data
    $perf report --stdio --show-total-period -i /tmp/perf.data

## Other Resources

### Linux sourcecode
The perf tools sourcecode lives in the Linux kernel tree under /tools/perf. You will
find much more documentation in | /tools/perf/Documentation. To build manpages, info
pages and more, install these tools:

- asciidoc
- tetex-fonts
- tetex-dvips
- dialog
- tetex
- tetex-latex
- xmltex
- passivetex
- w3m
- xmlto

and issue a make install-man from /tools/perf. This step is also required to be able to
run perf help <command>.
