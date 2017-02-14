;; test map-int
(map-int #'identity 10)

(map-int #'(lambda (x) (random 100))
         10)


;; test filter
(filter #'(lambda (x)
            (and (evenp x)
                 (+ x 10)))
        '(1 2 3 4 5 6 7))


;; test most
(most #'length '((a b) (a b c) (a)))
