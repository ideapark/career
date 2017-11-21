;; in-S? : N → Bool
;; usage: (in-S? n) = #t if n is S, #f otherwise
(define in-S?
  (lambda (n)
    (if (zero? n) #t
	(if (>= (- n 3) 0)
	    (in-S? (- n 3))
	    #f))))

;; --------------------------------
;; The Smaller-Subproblem Principle
;; --------------------------------
;; If we can reduce a problem to a smaller subproblem, we can call
;; the procedure that solves the problem to solve the subproblem.

;; list-length : List → Int
;; usage: (list-length l) = the length of l
(define list-length
  (lambda (lst)
    (if (null? lst)
	0
	(+ 1 (list-length (cdr lst))))))

;; nth-element : List × Int → SchemeVal
;; usage: (nth-element lst n) = the n-th element of lst
(define nth-element
  (lambda (lst n)
    (if (null? lst)
	(report-list-too-short n)
	(if (zero? n)
	    (car lst)
	    (nth-element (cdr lst) (- n 1))))))

(define report-list-too-short
  (lambda (n)
    (eopl:error 'nth-element
		"List too short by ~s elements.~%" (+ n 1))))
