;; Finding fixed points of functions

(define tolerance 0.00001)
(define (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guess))

;; f(x) = cos(x)
(fixed-point cos 1.0)

;; f(x) = sin(x) + cos(x)
(fixed-point (lambda (x) (+ (sin x) (cos y)))
             1.0)

;; Square root of x; finding a y such that y^2 = x. putting this
;; equation into the equivalent form y = x/y, we recognize that we are
;; looking for a fixed point of the y = x/y, but it will oscillations,
;; so we make a new guess by averaging y with x/y, so that the next
;; guess after y is (1/2)(y+x/y) instead of x/y. So the square root of
;; x is simply the process of looking for a fixed point of: y =
;; (1/2)(y+x/y).
(define (sqrt x)
  (fixed-point (lambda (y) (average y (/ x y)))
               1.0))
