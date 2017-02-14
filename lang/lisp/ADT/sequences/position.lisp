(position #\a "fantasia")

(position #\a "fantasia" :start 3 :end 5)

(position #\a "fantasia" :from-end t)

(position 'a '((c d) (a b)) :key #'car)

(position '(a b) '((a b) (c d)))

(position '(a b) '((a b) (c d)) :test #'equal)

(position 3 '(1 0 7 5) :test #'<)

(position-if #'oddp '(2 3 4 5))
