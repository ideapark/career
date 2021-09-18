# Kubernetes Security Principles

## Defense in Depth

Picture a medieval castle under siege. It has strong, high walls to
keep undesirables out. The wall is surrounded by a moat, with access
via a drawbridge that is lowered only occasionally to let people in
and out. The castle has thick doors, and bars across any
windows. Archers patrol the castle walls, ready to fire at any
attacker.

The castle has several layers of defense. Attackers who can swim might
be prepared to cross the moat, but then they have the walls to scale,
and the likelihood of being picked off by an archer. It might be
possible to compromise any given layer in the defensive structure, but
by having several layers, it’s hard for an attacker to successfully
enter the castle.

In the same way, it’s preferable to have several layers of defense
against attacks on your Kubernetes cluster. If you’re relying on a
single defensive measure, attackers might find their way around it.

## Least Privilege

The principle of least privilege tells us to restrict access so that
different components can access only the information and resources
they need to operate correctly. In the event of a component being
compromised, an attacker can reach only the subset of information and
resources available to that component. This limits the “blast radius”
of the attack.

## Limiting the Attack Surface

The attack surface is the set of all possible ways a system can be
attacked. The more complex the system, the bigger the attack surface,
and therefore the more likely it is that an attacker will find a way
in.

Consider our castle metaphor again: the longer the length of the
castle walls, the more archers we would need to patrol them
effectively. A circular castle will be most efficient from this point
of view; a complicated shape with lots of nooks and crannies would
need more archers for the same interior volume.

In software systems, the fundamental way to reduce the attack surface
is to minimize the amount of code. The more code that’s present in the
system, the more likely it is that it has vulnerabilities. The greater
the complexity, the more likely that latent vulnerabilities exist,
even in well-tested code.
