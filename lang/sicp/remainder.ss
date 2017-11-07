(define (remainder n d)
  (if (< n d)
      n
      (remainder (- n d) d)))

;; ---------- TESTS ----------
(remainder 10 7)
