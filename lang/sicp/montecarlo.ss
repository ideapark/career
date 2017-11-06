;; Monte Carlo simulation
;;
;; The Monte Carlo method consists of choosing sample experiments at random from
;; a large set and then making deductions on the basis of the probabilities
;; estimated from tabulating the results of those experiments

(define (estimate-pi trials)
  (sqrt (/ 6 (monte-carlo trials cesaro-test))))

(define (cesaro-test)
  (= (gcd (rand) (rand)) 1))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
	   (/ trials-passed trials))
	  ((experiment)
	   (iter (- trials-remaining 1)
		 (+ trials-passed 1)))
	  (else (iter (- trials-remaining 1)
		      trials-passed))))
  (iter trials 0))

;; ---------- TEST ----------
(estimate-pi 10000)
