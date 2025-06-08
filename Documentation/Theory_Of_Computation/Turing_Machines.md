TURING MACHINES
---------------

A Turing machine is a 7-tuple, (Q,Σ,Γ,δ,q₀,qᵃ,qʳ), where
Q, Σ, Γ are all finite sets and

1. Q is the set of states,
2. Σ is the input alphabet not containing the blank symbol (␣),
3. Γ is the tape alphabet, where ␣ ∈ Γ and Σ ⊆ Γ,
4. δ: Q × Γ → Q×Γ×{L,R} is the transition function,
5. q₀ ∈ Q is the start state,
6. qᵃ ∈ Q is the accept state, and
7. qʳ ∈ Q is the reject state, where qʳ ≠ qᵃ.
