(accumulate append
            nil
            (map (lambda (i)
                    (map (lambda (j) (list i j))
                         (enumerate-interval 1 (- i 1))))
                 (enumerate-interval 1 n)))

(define (flatmap proc seq)
    (accumulate append nil (map proc seq)))

(define (permutations s)
    (if (null? s)              ; empty set?
        (list nil)             ; sequence containing empty set
        (flatmap (lambda (x)
                    (map (lambda (p) (cons x p))
                         (permutations (remove x s))))
                 s)))

(define (remove item sequence)
    (filter (lambda (x) (not (= x item)))
            sequence))
