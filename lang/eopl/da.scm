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

;; empty-env : () → Env
(define empty-env
  (lambda () (list 'empty-env)))

;; extend-env : Var × SchemeVal × Env → Env
(define extend-env
  (lambda (var val env)
    (list 'extend-env var val env)))

;; apply-env : Env × Var → SchemeVal
(define apply-env
  (lambda (env search-var)
    (cond ((eqv? (car env) 'empty-env)
	   (report-no-binding-found search-var))
	  ((eqv? (car env) 'extend-env)
	   (let ((saved-var (cadr env))
		 (saved-val (caddr env))
		 (saved-env (cadddr env)))
	     (if (eqv? search-var saved-var)
		 saved-val
		 (apply-env saved-env search-var))))
	  (else
	   (report-invalid-env env)))))

(define report-no-binding-found
  (lambda (search-var)
    (error 'apply-env "No binding for ~s" search-var)))

(define report-invalid-env
  (lambda (env)
    (error 'apply-env "Bad environment: ~s" env)))


;; parse-expression : SchemeVal → LcExp
(define parse-expression
  (lambda (datum)
    (cond ((symbol? datum) (var-exp datum))
	  ((pair? datum) (if (eqv? (car datum) 'lambda)
			     (lambda-exp
			      (car (cadr datum))
			      (parse-expression (caddr datum)))
			     (app-exp
			      (parse-expression (car datum))
			      (parse-expression (cadr datum)))))
	  (else (report-invalid-concrete-syntax datum)))))

;; unparse-lc-exp : LcExp → SchemeVal
(define unparse-lc-exp
  (lambda (exp)
    (cases lc-exp exp
	   (var-exp (var) var)
	   (lambda-exp (bound-var body)
		       (list 'lambda (list bound-var)
			     (unparse-lc-exp body)))
	   (app-exp (rator rand)
		    (list (unparse-lc-exp rator)
			  (unparse-lc-exp rand))))))
