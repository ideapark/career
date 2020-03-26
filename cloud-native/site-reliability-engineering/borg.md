# Borg: Birth of the Warehouse-Scale Computer

Another way to understand the development of our attitude toward automation, and
when and where that automation is best deployed, is to consider the history of
the development of our cluster management systems Like MySQL on Borg, which
demonstrated the success of converting manual operations to automatic ones, and
the cluster turnup process, which demonstrated the downside of not thinking
carefully enough about where and how automation was implemented, developing
cluster management also ended up demonstrating another lesson about how
automation should be done. Like our previous two examples, something quite
sophisticated was created as the eventual result of continuous evolution from
simpler beginnings.

Google’s clusters were initially deployed much like everyone else’s small
networks of the time: racks of machines with specific purposes and heterogeneous
configurations. Engineers would log in to some well-known “master” machine to
perform administrative tasks; “golden” binaries and configuration lived on these
masters. As we had only one colo provider, most naming logic implicitly assumed
that location. As production grew, and we began to use multiple clusters,
different domains (cluster names) entered the picture. It became necessary to
have a file describing what each machine did, which grouped machines under some
loose naming strategy. This descriptor file, in combination with the equivalent
of a parallel SSH, allowed us to reboot (for example) all the search machines in
one go. Around this time, it was common to get tickets like “search is done with
machine x1, crawl can have the machine now.”

Automation development began. Initially automation consisted of simple Python
scripts for operations such as the following:

Service management: keeping services running (e.g., restarts after segfaults)
Tracking what services were supposed to run on which machines Log message
parsing: SSHing into each machine and looking for regexps Automation eventually
mutated into a proper database that tracked machine state, and also incorporated
more sophisticated monitoring tools. With the union set of the automation
available, we could now automatically manage much of the lifecycle of machines:
noticing when machines were broken, removing the services, sending them to
repair, and restoring the configuration when they came back from repair.

But to take a step back, this automation was useful yet profoundly limited, due
to the fact that abstractions of the system were relentlessly tied to physical
machines. We needed a new approach, hence Borg [Ver15] was born: a system that
moved away from the relatively static host/port/job assignments of the previous
world, toward treating a collection of machines as a managed sea of resources.
`Central to its success—and its conception—was the notion of turning cluster
management into an entity for which API calls could be issued, to some central
coordinator.` This liberated extra dimensions of efficiency, flexibility, and
reliability: unlike the previous model of machine “ownership,” Borg could allow
machines to schedule, for example, batch and user-facing tasks on the same
machine.

This functionality ultimately resulted in continuous and automatic operating
system upgrades with a very small amount of constant effort—effort that does not
scale with the total size of production deployments. Slight deviations in
machine state are now automatically fixed; brokenness and lifecycle management
are essentially no-ops for SRE at this point. Thousands of machines are born,
die, and go into repairs daily with no SRE effort. To echo the words of Ben
Treynor Sloss: by taking the approach that this was a software problem, the
initial automation bought us enough time to turn cluster management into
something autonomous, as opposed to automated. We achieved this goal by bringing
ideas related to data distribution, APIs, hub-and-spoke architectures, and
classic distributed system software development to bear upon the domain of
infrastructure management.

An interesting analogy is possible here: we can make a direct mapping between
the single machine case and the development of cluster management abstractions.
In this view, rescheduling on another machine looks a lot like a process moving
from one CPU to another: of course, those compute resources happen to be at the
other end of a network link, but to what extent does that actually matter?
Thinking in these terms, rescheduling looks like an intrinsic feature of the
system rather than something one would “automate”—humans couldn’t react fast
enough anyway. Similarly in the case of cluster turnup: in this metaphor,
cluster turnup is simply additional schedulable capacity, a bit like adding disk
or RAM to a single computer. However, a single-node computer is not, in general,
expected to continue operating when a large number of components fail. The
global computer is—it must be self-repairing to operate once it grows past a
certain size, due to the essentially statistically guaranteed large number of
failures taking place every second. This implies that as we move systems up the
hierarchy from manually triggered, to automatically triggered, to autonomous,
some capacity for self-introspection is necessary to survive.
