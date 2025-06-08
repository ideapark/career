FINITE AUTOMATA
---------------

A finite automaton is a 5-tuple (Q,Σ,δ,q₀,F), where

  1. Q is a finite set of states,
  2. Σ is a finite alphabet,
  3. δ: Q × Σ → Q is the transition function,
  4. q₀ ∈ Q is the start state, and
  5. F ⊆ Q is the set of accept states.

Let M = (Q,Σ,δ,q₀,F) be a finite automaton and let w = w₁w₂···wₑ be a
string where each wᵢ is a member of the alphabet Σ. Then M accepts w
if a sequence of states r₀,r₁,...,rₑ in Q exists with three
conditions:

  1. r₀ = q₀,
  2. δ(rᵢ,wᵢ₊₁) = rᵢ₊₁, for i=0, ..., e−1, and
  3. rₑ ∈ F.

A language is called a regular language if some finite automaton
recognizes it.


REGULAR OPERATIONS
------------------

Let A and B be languages. We define the regular operations union,
concatenation, and star as follows:

  1. Union: A ∪ B = {x| x ∈ A or x ∈ B}.
  2. Concatenation: A ◦ B = {xy| x ∈ A and y ∈ B}.
  3. Star: A* = {x₁x₂...xₑ| e ≥ 0 and each xᵢ ∈ A}.


NONDETERMINISTIC FINITE AUTOMATON
---------------------------------

In an NFA, the transition function takes a state and an input symbol
or the empty string and produces the set of possible next states. In
order to write the formal definition, we need to set up some
additional notation. For any set Q we write 𝒫(Q) to be the collection
of all subsets of Q. Here 𝒫(Q) is called the power set of Q. For any
alphabet Σ we write Σε to be Σ ∪ {ε}. Now we can write the formal
description of the type of the transition function in an NFA as
δ: Q × Σε → 𝒫(Q).

A nondeterministic finite automaton is a 5-tuple (Q,Σ,δ,q0,F), where

  1. Q is a finite set of states,
  2. Σ is a finite alphabet,
  3. δ: Q × Σε → 𝒫(Q)={R|R⊆Q} is the transition function,
  4. q0 ∈ Q is the start state, and
  5. F ⊆ Q is the set of accept states.

Let N = (Q,Σ,δ,q₀,F) be an NFA and w a string over the alphabet
Σ. Then we say that N accepts w if we can write w as w = y₁y₂···yₑ,
where each yᵢ is a member of Σε and a sequence of states r₀,r₁,...,rₑ
exists in Q with three conditions:

  1. r₀ = q₀,
  2. rᵢ₊₁ ∈ δ(rᵢ,yᵢ₊₁), for i=0, ..., e−1, and
  3. rₑ ∈ F.


EQUIVALENCE OF NFAs AND DFAs
----------------------------

PROOF Let N=(Q,Σ,δ,q₀,F) be the NFA recognizing some language A. We
construct a DFA M=(Q',Σ,δ',q₀',F') recognizing A. Before doing the
full construction, let’s first consider the easier case wherein N has
no ε arrows. Later we take the ε arrows into account.

1. Q' = 𝒫(Q).
   Every state of M is a set of states of N. Recall that 𝒫(Q) is the
   set of subsets of Q.

2. For R∈Q' and a∈Σ, let δ'(R,a) = {q∈Q| q∈δ(r,a) for some r∈R}. If R
   is a state of M, it is also a set of states of N. When M reads a
   symbol a in state R, it shows where a takes each state in
   R. Because each state may go to a set of states, we take the union
   of all these sets. Another way to write this expression is
   δ'(R,a)={union of the sets δ(r,a) for each possible r∈R}.

3. q₀' = {q₀}.
   M starts in the state corresponding to the collection containing
   just the start state of N.

4. F' = {R∈Q'| R contains an accept state of N}.
   The machine M accepts if one of the possible states that N could be
   in at this point is an accept state.

Now we need to consider the ε arrows. To do so, we set up an extra bit
of notation. For any state R of M, we define E(R) to be the collection
of states that can be reached from members of R by going only along ε
arrows, including the members of R themselves. Formally, for R⊆Q let

  E(R) = {q| q can be reached from R by traveling along 0 or more ε arrows}.

Then we modify the transition function of M to place additional
fingers on all states that can be reached by going along ε arrows
after every step. Replacing δ(r,a) by E(δ(r,a)) achieves this
effect. Thus

  δ'(R,a) = {q∈Q| q∈E(δ(r,a)) for some r∈R}.

Additionally, we need to modify the start state of M to move the
fingers initially to all possible states that can be reached from the
start state of N along the ε arrows. Changing q₀' to be E({q₀})
achieves this effect. We have now completed the construction of the
DFA M that simulates the NFA N.

The construction of M obviously works correctly. At every step in the
computation of M on an input, it clearly enters a state that
corresponds to the subset of states that N could be in at that
point. Thus our proof is complete.


REGULAR LANGUAGES ARE EQUIVALENT TO NFAs/DFAs
---------------------------------------------

A language is regular if and only if some nondeterministic finite
automaton recognizes it.

Regular Language is closed under regular operations of Union,
Concatenation and Star. So more complicated and expressive regular
languages can be constructed from simpler ones by conducting these
operations, the resulting products are regular languages as well.

  1. The class of regular languages is closed under the union operation.
  2. The class of regular languages is closed under the concatenation operation.
  3. The class of regular languages is closed under the star operation.


REGULAR EXPRESSION
------------------

Say that R is a regular expression if R is

  1. a for some a in the alphabet Σ,
  2. ε,
  3. ∅,
  4. (R₁∪R₂), where R1 and R2 are regular expressions,
  5. (R₁◦R₂), where R1 and R2 are regular expressions, or
  6. (R₁∗), where R1 is a regular expression.

In items 1 and 2, the regular expressions a and ε represent the
languages {a} and {ε}, respectively. In item 3, the regular expression
∅ represents the empty language. In items 4, 5, and 6, the expressions
represent the languages obtained by taking the union or concatenation
of the languages R₁ and R₂, or the star of the language R₁,
respectively.


GENERALIZED NONDETERMINISTIC FINITE AUTOMATON (GNFA)
----------------------------------------------------

A generalized nondeterministic finite automaton is a 5-tuple,
(Q,Σ,δ,qˢ,qᵃ), where

  1. Q is the finite set of states,
  2. Σ is the input alphabet,
  3. δ: (Q−{qᵃ} × Q−{qˢ}) → R is the transition function,
  4. qˢ is the start state, and
  5. qᵃ is the accept state.

A GNFA accepts a string w in Σ* if w=w₁w₂···wₑ, where each wᵢ is in Σ*
and a sequence of states q₀,q₁,...,qₑ exists such that

  1. q₀ = qˢ is the start state,
  2. qₑ = qᵃ is the accept state, and
  3. for each i, we have wᵢ∈L(Rᵢ), where Ri=δ(qᵢ₋₁,qᵢ); in other words,
     Rᵢ is the expression on the arrow from qᵢ₋₁ to qi.

Let M be the DFA for language A. Then we convert M to a GNFA G by
adding a new start state and a new accept state and additional
transition arrows as necessary. We use the procedure CONVERT(G), which
takes a GNFA and returns an equivalent regular expression. This
procedure uses recursion, which means that it calls itself. An
infinite loop is avoided because the procedure calls itself only to
process a GNFA that has one fewer state. The case where the GNFA has
two states is handled without recursion.

- CONVERT(G):

1. Let k be the number of states of G.
2. If k=2, then G must consist of a start state, an accept state, and
   a single arrow connecting them and labeled with a regular
   expression R. Return the expression R.
3. If k>2, we select any state qrip∈Q different from qstart and
   qaccept and let G' be the GNFA (Q',Σ,δ',qstart,qaccept), where

     Q' = Q − {qᵣ},

   and for any qᵢ∈Q'−{qaccept} and any qⱼ∈Q'−{qstart}, let

     δ'(qᵢ,qⱼ) = (R₁)(R₂)∗(R₃)∪(R₄), for R₁ = δ(qᵢ,qᵣ),
                                         R₂ = δ(qᵣ,qᵣ),
                                         R₃ = δ(qᵣ,qⱼ), and
                                         R₄ = δ(qᵢ,qⱼ).
4. Compute CONVERT(G') and return this value.

NONREGULAR LANGUAGES
--------------------

Pumping Lemma: If A is a regular language, then there is a number p
(the pumping length) where if s is any string in A of length at least
p, then s may be divided into three pieces, s=xyz, satisfying the
following conditions:

  1. for each i ≥ 0, xyⁱz ∈ A,
  2. |y| > 0, and
  3. |xy| ≤ p.

The notation where |s| represents the length of string s, yⁱ means
that i copies of y are concatenated together, and y⁰ equals ε.  When
s is divided into xyz, either x or z may be ε, but condition 2 says
that y ≠ ε. Observe that without condition 2 the theorem would be
trivially true.  Condition 3 states that the pieces x and y together
have length at most p. It is an extra technical condition that we
occasionally find useful when proving certain languages to be
nonregular.
