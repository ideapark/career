;; Tree: Hierarchical Structures
(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        ((else (+ (count-leaves (car x))
                  (count-leaves (cdr x)))))))

(define x (cons (list 1 2) (list 3 4)))

;; (((1 2) 3 4) ((1 2) 3 4))
(count-leaves (list x x))

(define (double-tree tree)
  (map (lambda (subtree)
         (if (pair? subtree)
             (double-tree subtree)
             (* 2 subtree)))
       tree))

(double-tree (list x x))
