(defun tree1+ (tr)
  (cond ((null tr) nil)
        ((atom tr) 1+ tr))
        (t (cons (tree1+ (car tr))
                 (tree1+ (cdr tr)))))

(trace tree1+)

(tree1+ '((1 . 3) 5 . 7))

(untrace tree1+)
