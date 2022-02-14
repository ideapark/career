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


(define (sqrt x)
  (define (good-enough? guess)
    (< (abs (- (square guess) x)) 0.001))
  (define (improve guess)
    (average guess (/ x guess)))
  (define (sqrt-iter guess)
    (if (good-enough? guess)
        guess
        (sqrt-iter (improve guess))))
  (sqrt-iter 1.0))
