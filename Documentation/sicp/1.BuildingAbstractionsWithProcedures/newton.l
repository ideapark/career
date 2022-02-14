;; Square Roots by Newton's Method
;;
;; Computing the square root of 2 as follows, suppose our initial guess is 1:
;;
;;   GUESS              QUOTIENT                  AVERAGE
;;   1                  (2/1) = 2                 ((2+1)/2) = 1.5
;;   1.5                (2/1.5) = 1.3333          ((1.333+1.5)/2) = 1.4167
;;   1.4167             (2/1.4167) = 1.4118       ((1.4167+1.4118)/2) = 1.4142
;;   1.4142             ...                       ...
;;
;;
;; Procedural decomposition of the sqrt program.
;;
;;   sqrt +----o sqrt-iter
;;             |
;;             +-----o improve
;;             |     |
;;             |     +----o average
;;             |
;;             +-----o good-enough
;;                   |
;;                   +-----o square
;;                   |
;;                   +-----o abs

(define (sqrt-iter guess x)
  (if (good-enough? guess x)
      guess
      (sqrt-iter (improve guess x)
                 x)))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))

(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))

(define (sqrt x)
  (sqrt-iter 1.0 x))
