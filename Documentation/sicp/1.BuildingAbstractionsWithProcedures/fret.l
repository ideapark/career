;; Procedures as Returned Values

(define (average-damp f)
  (lambda (x) (average x (f x))))

;; (x+x^2)/2
((average-damp square) 10)

(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y)))
               1.0))
