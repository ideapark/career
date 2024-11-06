;; Procedures that manipulate procedures are called higher-order procedures.
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))

;; sum-cubes:
;;            1^3 + 2^3 + 3^3 + ...
(define (inc n) (+ n 1))
(define (sum-cubes a b)
  (sum cube a inc b))
(sum-cubes 1 10)

;; sum-integers:
;;               1 + 2 + 3 + ...
(define (identity x) x)
(define (sum-integers a b)
  (sum identity a inc b))
(sum-integers 1 10)

;; pi-sum:
;;         π/8 = 1/(1*3) + 1/(5*7) + 1/(9*11) + ...
(define (pi-sum a b)
  (define (pi-term x)
    (/ 1.0 (* x (+ x 2))))
  (define (pi-next x)
    (+ x 4))
  (sum pi-term a pi-next b))
(* 8 (pi-sum 1 1000))
