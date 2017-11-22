;; Data Abstraction

(define plus
  (lambda (x y)
    (if (is-zero? x)
	y
	(successor (plus (predecessor x y))))))

;; Unary representation
(define zero (lambda () '()))
(define is-zero? (lambda (n) (null? n)))
(define successor (lambda (n) (cons #t n)))
(define predecessor (lambda (n) (cdr n)))

;; Scheme number representation
(define zero (lambda () 0))
(define is-zero? (lambda (n) (zero? n)))
(define successor (lambda (n) (+ n 1)))
(define predecessor (lambda (n) (- n 1)))

;; Bignum representation
;; Page 57
