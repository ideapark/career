;; Fixed Point
;;
;; f(x) = x
;; f(x), f(f(x)), f(f(f(x))), ...
(define tolerance 0.0001)

(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
	  next
	  (try next))))
  (try first-guess))

(define (average-damp f)
  (define (average a b)
    (/ (+ a b) 2.0))
  (lambda (x) (average x (f x))))

;; y = x^3
(define (cube-root x)
  (define (square a)
    (* a a))
  (fixed-point (average-damp (lambda (y) (/ x (square y))))
	       1.0))

;; cos
(fixed-point cos 1.0)

;; y = sin(y) + cos(y)
(fixed-point (lambda (y) (+ (sin y) (cos y)))
	     1.0)

;; y = x^3
(cube-root 10.0)
