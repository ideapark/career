;; Using procedure to implement
;;   cons
;;   car
;;   cdr
(define (cons x y)
  (define (dispatch m)
    (cond ((= 0 m) x)
          ((= 1 m) y)
          (else (error "Argument not 0 or 1 -- CONS" m))))
  dispatch)

(define (car z) (z 0))
(define (cdr z) (z 1))

;; Testing: cons, car, cdr
(car (cons 3 5))
(cdr (cons 5 7))
