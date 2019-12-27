;; Greatest Common Divider
;; If r = a % b
;; Then
;; 	GCD(a,b) = GCD(b,r)
;;
;; GCD(206,40) = GCD(40,6)
;;             = GCD(6,4)
;;             = GCD(4,2)
;;             = GCD(2,0)
;;             = 2
(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))

;; ---------- TESTS ----------
(gcd 1024 250)
