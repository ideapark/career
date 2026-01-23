Standard algorithm for inserting φ-functions
============================================

```text
 1 for v:variable names in original program do
 2     F ← {}  ▷ set of basic blocks where φ is added
 3     W ← {}  ▷ set of basic blocks that contain definitions of v
 4     for d ∈ Defs(v) do
 5         let B be the basic block containing d
 6         W ← W ∪ {B}
 7     while W ≠ {} do
 8         remove a basic block X from W
 9         for Y:basic block ∈ DF(X) do
10             if Y ∉ F then
11                 add v ← φ(...) at entry of Y
12                 F ← F ∪ {Y}
13                 if Y ∉ Defs(v) then
14                     W ← W ∪ {Y}
```
