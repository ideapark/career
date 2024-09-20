CONTEXT-FREE GRAMMAR (CFG)
--------------------------

A context-free grammar is a 4-tuple (V,Σ,R,S), where

1. V is a finite set called the variables,
2. Σ is a finite set, disjoint from V, called the terminals,
3. R is a finite set of rules, with each rule being a variable and a string of variables and terminals, and
4. S ∈ V is the start variable.


DESIGNING CONTEXT-FREE GRAMMARS
-------------------------------

As with the design of finite automata, the design of context-free
grammars requires creativity. Indeed, context-free grammars are even
trickier to construct than finite automata because we are more
accustomed to programming a machine for specific tasks than we are to
describing languages with grammars. The following techniques are
helpful, singly or in combination, when you’re faced with the problem
of constructing a CFG.

First, many CFLs are the union of simpler CFLs. If you must construct
a CFG for a CFL that you can break into simpler pieces, do so and then
construct individual grammars for each piece. These individual
grammars can be easily merged into a grammar for the original language
by combining their rules and then adding the new rule S→S1|S2|···|Sk,
where the variables Si are the start variables for the individual
grammars. Solving several simpler problems is often easier than
solving one complicated problem.
