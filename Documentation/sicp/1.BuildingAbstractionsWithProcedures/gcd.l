;; The greatest common divisor (GCD) of two integers a and b is
;; defined to be the largest integer that divides both a and b with no
;; remainder.
;;
;; If r is the remainder when a is divided by b, then the common
;; divisors of a and b are precisely the same as the common divisors
;; of b and r. Thus, we can use the equation
;;
;;     GCD(a,b) = GCD(b,r)
;;
;;  GCD(206,40) = GCD(40,6)
;;              = GCD(6,4)
;;              = GCD(4,2)
;;              = GCD(2,0)
;;              = 2
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
