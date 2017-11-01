;; Newton's method
(define dx 0.00001)

(define (deriv g)
  (lambda (x) (/ (- (g (+ x dx)) (g x)) dx)))

;; ---------- TESTS ----------
(define (cube x) (* x x x))
((deriv cube) 5)

(define (newton-transform g)
  (lambda (x) (- x (/ (g x) ((deriv g) x)))))
(define (newtons-method g guess)
  (fixed-point (newton-transform g) guess))

;; Square root
(define (sqrt x)
  (newtons-method (lambda (y) (- (square y) x)) 1.0))
