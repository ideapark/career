;; box-and-pointer

;; closure property: combining things with that operation can
;; themselves be combined using the same operation.
;;
;;    cons

;; [+-+]
;;  | |
;;  v v
;;  1 2
(cons 1 2)

;; [+-----+]
;;  |     |
;; [+-+][+-+]
;;  | |  | |
;;  v v  v v
;;  1 2  3 4
(cons (cons 1 2)
      (cons 3 4))

;; (list <a1> <a2> ... <an>)
(cons 1
      (cons 2
            (cons 3
                  (cons 4 nil))))

;; (1 2 3 4)
(list 1 2 3 4)
(cons 5 (list 1 2 3 4))
(cons 5 '(1 2 3 4))

;; list operation
(define (list-ref items n)
  (if (= n 0)
      (car items)
      (list-ref (cdr items) (- n 1))))

(define squares (list 1 4 9 16 25))
(list-ref squares 3)
