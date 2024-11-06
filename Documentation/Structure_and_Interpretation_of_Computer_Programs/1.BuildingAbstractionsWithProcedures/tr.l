;; Tree-Recursion:
;;
;;          +-> 0                     if n = 0
;;          |
;; Fib(n) = +-> 1                     if n = 1
;;          |
;;          +-> Fib(n-1) + Fib(n-2)   otherwise
;;
;;
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1))
                 (fib (- n 2))))))

;; The tree-recursive process generated in computing (fib 5).
;;
;; fib(5) +--->fib(3) +---> fib(1) +---> 1
;;        |           |
;;        |           +---> fib(2) +---> fib(0) +---> 0
;;        |                        |
;;        |                        +---> fib(1) +---> 1
;;        |
;;        +--->fib(4) +---> fib(2) +---> fib(0) +---> 0
;;                    |            |
;;                    |            +---> fib(1) +---> 1
;;                    |
;;                    +---> fib(3) +---> fib(1) +---> 1
;;                                 |
;;                                 +---> fib(2) +---> fib(0) +---> 0
;;                                              |
;;                                              +---> fib(1) +---> 1
(fib 5)
