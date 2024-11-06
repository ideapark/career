;; Finding roots of equations by the half-interval method
;;
;; The half-interval method is a simple but powerful technique for
;; finding roots of an equation f(x) = 0, where f is a continuous
;; function. The idea is that, if we are given points a and b such
;; that f(a) < 0 < f(b), then f must have at least one zero between a
;; and b. To locate a zero, let x be the average of a and b and
;; compute f(x). If f(x) > 0, then f must have a zero between a and
;; x. If f(x) < 0, then f must have a zero between x and b. Continuing
;; in this way, we can identify smaller and smaller intervals on which
;; f must have a zero. When we reach a point where the interval is
;; small enough, the process stops.
(define (search f neg-point pos-point)
  (let ((mid-point (average neg-point pos-point)))
    (if (close-enough? neg-point pos-point)
        mid-point
      (let ((test-value (f mid-point)))
        (cond ((positive? test-value)
               (search f neg-point mid-point))
              ((negative? test-value)
               (search f mid-point pos-point))
              (else mid-point))))))

(define (close-enough? x y)
  (< (abs (- x y)) 0.001))

(define (half-interval-method f a b)
  (let ((a-value (f a))
        (b-value (f b)))
    (cond ((and (negative? a-value) (positive? b-value))
           (search f a b))
          ((and (negative? b-value) (positive? a-value))
           (search f b a))
          (else
           (error "Values are not of opposite sign" a b)))))

;; f(x) = sin(x); where 2.0 <= x <= 4.0
(half-interval-method sin 2.0 4.0)

;; f(x) = x^3 - 2x - 3; where 1.0 < x < 2.0
(half-interval-method (lambda (x) (- (* x x x) (* 2 x) 3))
                      1.0
                      2.0)
