;; Linear Recursion and Iteration
;;
;; n! = n * (n-1) * (n-2) * * * 3 * 2 * 1
;; n! = n * [(n-1) * (n-2) * * * 3 * 2 * 1] = n * (n-1)!
;;
(define (factorial n)
  (if (= n 1)
      1
      (* n (factorial (- n 1)))))

;; A linear rexursive process for computing 6!.
;;
;; (factorial 6)
;; (* 6 (factorial 5))
;; (* 6 (* 5 (factorial 4)))
;; (* 6 (* 5 (* 4 (factorial 3))))
;; (* 6 (* 5 (* 4 (* 3 (factorial 2)))))
;; (* 6 (* 5 (* 4 (* 3 (* 2 (factorial 1))))))
;; (* 6 (* 5 (* 4 (* 3 (* 2 1)))))
;; (* 6 (* 5 (* 4 (* 3 2))))
;; (* 6 (* 5 (* 4 6)))
;; (* 6 (* 5 24))
;; (* 6 120)
;; 720
(factorial 6)
