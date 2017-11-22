;; LET: A Simple Language

(define-datatype program program?
  (a-program
   (exp1 expression?)))

(define-datatype expression expression?
  (const-exp
   (num number?))
  (diff-exp
   (exp1 expression?)
   (exp2 expression?))
  (zero?-exp
   (exp1 expression?))
  (if-exp
   (exp1 expression?)
   (exp2 expression?)
   (exp3 expression?))
  (var-exp
   (var identifier?))
  (let-exp
   (var identifier?)
   (exp1 expression?)
   (body expression?)))

;; init-env : () → Env
;; usage: (init-env) = [i=1,v=5,x=10]
(define init-env
  (lambda ()
    (extend-env 'i (num-val 1)
		(extend-env 'v (num-val 5)
			    (extend-env 'x (num-val 10)
					(empty-env))))))

(define-datatype expval expval?
  (num-val (num number?))
  (bool-val (bool boolean?)))

;; expval->num : ExpVal → Int
(define expval->num
  (lambda (val)
    (cases expval val
	   (num-val (num) num)
	   (else (report-expval-extractor-error 'num val)))))

;; expval->bool : ExpVal → Bool
(define expval->bool
  (lambda (val)
    (cases expval val
	   (bool-val (bool) bool)
	   (else (report-expval-extractor-error 'bool val)))))

;; run : String → ExpVal
(define run
  (lambda (string)
    (value-of-program (scan&parse string))))

;;value-of-program : Program → ExpVal
(define value-of-program
  (lambda (pgm)
    (cases program pgm
	   (a-program (exp1)
		      (value-of exp1 (init-env))))))
