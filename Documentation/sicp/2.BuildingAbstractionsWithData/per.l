;; Permutations of Set:
;;
;; For the set of {1,2,3}, the permutations will be:
;;
;;   {1,2,3}
;;   {1,3,2}
;;   {2,1,3}
;;   {2,3,1}
;;   {3,1,2}
;;   {3,2,1}
;;
(define (permutations s)
  (if (null? s)     ; empty set?
      (list nil)    ; sequence containing empty set
      (flatmap (lambda (x)
                 (map (lambda (p) (cons x p))
                      (permutations (remove x s))))
               s)))

(define (remove item sequence)
  (filter (lambda (x) (not (= x item)))
          sequence))
