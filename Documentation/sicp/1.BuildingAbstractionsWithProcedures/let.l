;; Using let to create local variables
;;
;;   f(x,y) = x(1+xy)^2 + y(1-y) + (1+xy)(1-y)
;;
;;    Let:
;;      a = 1+xy
;;      b = 1-y
;;
;;   f(x,y) = xa^2 + yb + ab
;;
;;
;; (let ((<var1> <exp1>)
;;       (<var2> <exp2>)
;;       ...
;;       (<varn> <expn))
;;   <body>)
;;
;; A let expression is simply syntactic sugar for the underlying
;; lambda application.
;;
;; ((lambda (<var1> ... <varn>)
;;      <body>)
;;   <exp1>
;;   ...
;;   <expn>)
;;
(define (f x y)
  (let ((a (+ 1 (* x y)))
        (b (- 1 y)))
    (+ (* x (square a))
       (* y b)
       (* a b))))
