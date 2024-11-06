;; To evaluate a combination, do the following:
;;
;;   1. evaluate the subexpressions of the combination
;;
;;   2. apply the procedure that is the value of the leftmost
;;      subexpression (the operator) to the arguments that are the values
;;      of the other subexpressions (the operands)
(* (+ 2 (* 4 6))
   (+ 3 5 7))

;; Tree accumulation
;;
;; We take of the primitive cases by stipulating that:
;;
;;   1. the values of numerals are the numbers that they name,
;;
;;   2. the values of built-in operators are the machine instruction
;;      sequences that carry out the corresponding operations, and
;;
;;   3. the values of other names are the objects associated with
;;      those names in the environment.
;;
;;
;; 390 o---- *
;;     |
;;     |    26
;;     +----o---- +
;;     |    |
;;     |    +---- 2
;;     |    |
;;     |    |    24
;;     |    +----o---- *
;;     |         |
;;     |         +---- 4
;;     |         |
;;     |         +---- 6
;;     |
;;     |    15
;;     +----o---- +
;;          |
;;          +---- 3
;;          |
;;          +---- 5
;;          |
;;          +---- 7
