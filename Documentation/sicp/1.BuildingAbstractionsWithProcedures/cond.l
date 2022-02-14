;;
;;       +->  r if r > 0
;;       |
;; |x| = +->  0 if r == 0
;;       |
;;       +-> -r if r < 0
;;
(define (abs x)
  (cond ((> x 0) x)
        ((= x 0) 0)
        ((< x 0) (- x))))

;; Predicate is used for procedures that return true or false, as well
;; as for expressions that evaluate to true or false. Primitive
;; predicates: >, <, =
(define (abs x)
  (cond ((< x 0) (- x))
        (else x)))

;; A restricted type of conditional that can be used when there are
;; precisely two cases in the case analysis.
;;
;; (if <predicate> <consequent> <alternative>)
;;
(define (abs x)
  (if (< x 0)
      (- x)
      x))

;; Built-in compound predicates
;;
;; (and <e1> ... <en>)
;; (or  <e1> ... <en>)
;; (not <e>)
(define (>= x y)
  (or (> x y) (= x y)))

(define (>= x y)
  (not (< x y)))
