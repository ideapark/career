;; test compose
(mapcar (compose #'list #'round #'sqrt)
        '(4 9 16 25))

;; test disjoin
(mapcar (disjoin #'integerp #'symbolp)
        '(a "a" 2 3))

;; test conjoin
(mapcar (conjoin #'integerp #'oddp)
        '(a "a" 2 3))

;; test curry/rcurry
(curry #'+ 3)
(rcurry #'+ 3)
(funcall (curry #'- 3) 2)
(funcall (rcurry #'- 3) 2)
