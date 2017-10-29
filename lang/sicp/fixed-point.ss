(define tolerance 0.0001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
	  next
	  (try next))))
  (try fist-guess))

;; cos
(fixed-point cos 1.0)

;; y = sin y + cos y
(fixed-point (lambda (y) (+ (sin y) (cos y)))
             1.0)

(define (average-damp f)
  (lambda (x) (average x (f x))))

;; y = x^3
(define (cube-root x)
  (fixed-point (average-damp (lambda (y) (/ x (square))))
	       1.0))
