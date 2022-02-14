;; Primitive number
486

;; Builtin primitive procedures
(+ 486 486)
(- 1000 334)
(* 5 99)
(/ 10 5)
(+ 2.7 10)

;; Prefix natation:
;;   (operator operand operand operand ...)
;;
;; Advantages:
;;   1. it can accommondate precedures that may take
;;      arbitrary number of arguments, No ambiguity can arise,
;;      because the operator is always the leftmost element and
;;      the entire combination is delemited by the parentheses.
(+ 21 35 12 7)
(* 25 4 12)
;;
;;   2. second advantage of prefix notation is that it extends
;;      in a straightforward way to allow combinations to be
;;      nested, that is, to have combinations whose elements
;;      are themselves combinations:
(+ (* 3 5) (- 10 6))
