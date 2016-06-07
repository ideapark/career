(define (sum term a next b)
    (if (> a b)
        0
        (+ (term a)
           (sum term (next a) next b))))
; sum of cube
(define (inc n) (+ n 1))
(define (sum-cubes a b)
    (sum cube a inc b))
(sum-cubes 1 10)

; sum of integers
(define (identity x) x)
(define (sum-integers a b)
    (sum identity a inc b))
(sum-integers 1 10)

; sum of pi
(define (pi-sum a b)
    (define (pi-term x)
        (/ 1.0 (* x (+ x 2))))
    (define (pi-next x)
        (+ x 4))
    (sum pi-term a pi-next b))
(* 8 (pi-sum 1 1000))
