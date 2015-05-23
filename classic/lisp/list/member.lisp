(member 'b '(a b c))

(member '(a) '((a) (z)) :test #'equal)

(member 2 '((1) (2)) :key #'car :test #'equal)

(member 2 '((1) (2)) :test #'equal :key #'car)

(member-if #'oddp '(2 3 4))
