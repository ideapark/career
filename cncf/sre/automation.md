# The Value of Automation

- Consistency

Although scale is an obvious motivation for automation, there are many other
reasons to use it. Take the example of university computing systems, where many
systems engineering folks started their careers. Systems administrators of that
background were generally charged with running a collection of machines or some
software, and were accustomed to manually performing various actions in the
discharge of that duty. One common example is creating user accounts; others
include purely operational duties like making sure backups happen, managing
server failover, and small data manipulations like changing the upstream DNS
servers’ resolv.conf, DNS server zone data, and similar activities. Ultimately,
however, this prevalence of manual tasks is unsatisfactory for both the
organizations and indeed the people maintaining systems in this way. For a
start, any action performed by a human or humans hundreds of times won’t be
performed the same way each time: even with the best will in the world, very few
of us will ever be as consistent as a machine. This inevitable lack of
consistency leads to mistakes, oversights, issues with data quality, and, yes,
reliability problems. In this domain — the execution of well-scoped, known
procedures the value of consistency is in many ways the primary value of
automation.

- A Platform

Automation doesn’t just provide consistency. Designed and done properly,
automatic systems also provide a platform that can be extended, applied to more
systems, or perhaps even spun out for profit.27 (The alternative, no automation,
is neither cost effective nor extensible: it is instead a tax levied on the
operation of a system.)

A platform also centralizes mistakes. In other words, a bug fixed in the code
will be fixed there once and forever, unlike a sufficiently large set of humans
performing the same procedure, as discussed previously. A platform can be
extended to perform additional tasks more easily than humans can be instructed
to perform them (or sometimes even realize that they have to be done). Depending
on the nature of the task, it can run either continuously or much more
frequently than humans could appropriately accomplish the task, or at times that
are inconvenient for humans. Furthermore, a platform can export metrics about
its performance, or otherwise allow you to discover details about your process
you didn’t know previously, because these details are more easily measurable
within the context of a platform.

- Faster Repairs

There’s an additional benefit for systems where automation is used to resolve
common faults in a system (a frequent situation for SRE-created automation). If
automation runs regularly and successfully enough, the result is a reduced mean
time to repair (MTTR) for those common faults. You can then spend your time on
other tasks instead, thereby achieving increased developer velocity because you
don’t have to spend time either preventing a problem or (more commonly) cleaning
up after it. As is well understood in the industry, the later in the product
lifecycle a problem is discovered, the more expensive it is to fix; see Testing
for Reliability. Generally, problems that occur in actual production are most
expensive to fix, both in terms of time and money, which means that an automated
system looking for problems as soon as they arise has a good chance of lowering
the total cost of the system, given that the system is sufficiently large.

- Faster Action

In the infrastructural situations where SRE automation tends to be deployed,
humans don’t usually react as fast as machines. In most common cases, where, for
example, failover or traffic switching can be well defined for a particular
application, it makes no sense to effectively require a human to intermittently
press a button called “Allow system to continue to run.” (Yes, it is true that
sometimes automatic procedures can end up making a bad situation worse, but that
is why such procedures should be scoped over well-defined domains.) Google has a
large amount of automation; in many cases, the services we support could not
long survive without this automation because they crossed the threshold of
manageable manual operation long ago.

- Time Saving

Finally, time saving is an oft-quoted rationale for automation. Although people
cite this rationale for automation more than the others, in many ways the
benefit is often less immediately calculable. Engineers often waver over whether
a particular piece of automation or code is worth writing, in terms of effort
saved in not requiring a task to be performed manually versus the effort
required to write it.28 It’s easy to overlook the fact that once you have
encapsulated some task in automation, anyone can execute the task. Therefore,
the time savings apply across anyone who would plausibly use the automation.
Decoupling operator from operation is very powerful.

Joseph Bironas, an SRE who led Google’s datacenter turnup efforts for a time,
forcefully argued:

"If we are engineering processes and solutions that are not automatable, we
continue having to staff humans to maintain the system. If we have to staff
humans to do the work, we are feeding the machines with the blood, sweat, and
tears of human beings. Think The Matrix with less special effects and more
pissed off System Administrators."
