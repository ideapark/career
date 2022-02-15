;; Fermat's Little Theorem:
;;
;; If n is a prime number and a is any positive integer less than n,
;; then a raised to the nth power is congruent to a modulo n.
;;
;; (Two numbers are said to be congruent modulo n if they both have
;; the same remainder when divided by n. The remainder of a number a
;; when divided by n is also referred to as the remainder of a modulo
;; n, or simply as a modulo n.)
;;
;; If n is not prime, then, in general, most of the numbers a < n will
;; not satisfy the above relation. This leads to the following
;; algorithm for testing primality: Given a number n, pick a random
;; number a < n and compute the remainder of an modulo n. If the
;; result is not equal to a, then n is certainly not prime. If it is
;; a, then chances are good that n is prime. Now pick another random
;; number a and test it with the same method. If it also satisfies the
;; equation, then we can be even more confident that n is prime. By
;; trying more and more values of a, we can increase our confidence in
;; the result. This algorithm is known as the Fermat test.
(define (fermat-test n)
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it (+ 1 (random (- n 1)))))

(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        ((else
          (remainder (* base (expmod base (- exp 1) m))
                     m)))))

(define (fast-prime? n times)
  (cond ((= times 0) true)
        ((fermat-test n) (fast-prime? n (- times 1)))
        (else false)))
