;; Linear Iterative Process:
;;
;; An iterative process is one whose state can be summarized by a
;; fixed number of state variables, together with a fixed rule that
;; describes how the state variables should be updated as the process
;; moves from state to state and an (optional) end test that specifies
;; conditions under which the process should terminate.

;; A linear iterative process for computing 6!.
;;
;; (factorial 6)
;; (fact-iter   1 1 6)
;; (fact-iter   1 2 6)
;; (fact-iter   2 3 6)
;; (fact-iter   6 4 6)
;; (fact-iter  24 5 6)
;; (fact-iter 120 6 6)
;; (fact-iter 720 7 6)
;;
(define (factorial n)
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))
