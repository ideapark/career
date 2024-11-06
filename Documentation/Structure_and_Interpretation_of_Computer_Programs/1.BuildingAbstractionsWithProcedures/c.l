;; The number of ways to change amount a using n kinds of coins equals:
;;
;;   1. the number of ways to change amount a using all but the first
;;      kind of coin,
;;
;;   2. the number of ways to change amount a - d using all n kind of
;;      coins, where d is the denomination of the first kind of coin.
;;
(define (count-change amount)
  (cc amount 5))

(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1)
        ((or (< amount 0) (= kinds-of-coins 0)) 0)
        ((else (+ (cc amount
                      (- kinds-of-coins 1))
                  (cc (- amount
                         (first-denomination kinds-of-coins))
                      kinds-of-coins))))))

(define (first-denomination kinds-of-coins)
  (cond ((= kinds-of-coins 1) 1)
        ((= kinds-of-coins 2) 5)
        ((= kinds-of-coins 3) 10)
        ((= kinds-of-coins 4) 25)
        ((= kinds-of-coins 5) 50)))

;; Make change of 1 dollar
(count-change 100)
