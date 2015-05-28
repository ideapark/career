(load "shortest-path.lisp")

(setf net '((a b c) (b c) (c d)))

(cdr (assoc 'a net))

(shortest-path 'a 'd net)
