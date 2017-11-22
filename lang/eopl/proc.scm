;; proc? : SchemeVal → Bool
(define proc?
  (lambda (val)
    (procedure? val)))

;; procedure : Var × Exp × Env → Proc
(define procedure
  (lambda (var body env)
    (lambda (val)
      (value-of body (extend-env var val env)))))

;; apply-procedure : Proc × ExpVal → ExpVal
(define apply-procedure
  (lambda (proc1 val)
    (proc1 val)))

;; proc? : SchemeVal → Bool
;; procedure : Var × Exp × Env → Proc
(define-datatype proc proc?
  (procedure
   (var identifier?)
   (body expression?)
   (saved-env environment?)))

;; apply-procedure : Proc × ExpVal → ExpVal
(define apply-procedure
  (lambda (proc1 val)
    (cases proc proc1
	   (procedure (var body saved-env)
		      (value-of body (extend-env var val saved-env))))))
