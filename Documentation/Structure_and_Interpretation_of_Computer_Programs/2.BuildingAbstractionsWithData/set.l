;; Sets as unordered lists
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else (element-of-set? x (cdr set)))))

(define (adjoin-set x set)
  (if (element-of-set? x set)
      set
      (cons x set)))

(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (cons (car set1)
               (intersection-set (cdr set1) set2)))
        (else (intersection-set (cdr set1) set2))))

;; testing
(element-of-set? 5 '(1 2 3 4 5))
(adjoin-set 5 '(1 2 3 4 5))
(intersection-set '(1 2 3 4 5) '(3 4 5 6 7))

;; TODO: the above set implementation time complexity is θ(n^2);
;; consider using ordered list as set to speed up the time complexity
;; to θ(n).
