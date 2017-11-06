(define rand (let ((x random-init))
	       (lambda ()
		 (set! x (rand-update x))
		 x)))

;; fake implementation
(define (rand-init) 0)
(define (rand-update x) x+1)

;; ---------- TESTS ----------
(print (rand))
(print (rand))
(print (rand))
(print (rand))
