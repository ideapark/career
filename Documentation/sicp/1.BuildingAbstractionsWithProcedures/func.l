;; A much more powerful abstraction technique by which a compound
;; operation can be given a name and then referred to as a unit.
;;
;; (define (<name> <formal parameters) <body>)
;;
(define (square x) (* x x))

(square 21)
(square (+ 2 5))
(square (square 3))

;; Using square as a building block in defining other procedures.
;; x^2 + y^2
(define (sum-of-squares x y)
  (+ (square x) (square y)))

(sum-of-squares 3 4)

;; Now using sum-of-squares as a building block in constructing
;; further procedures:
(define (f a)
  (sum-of-squares (+ a 1) (* a 2)))

(f 5)
