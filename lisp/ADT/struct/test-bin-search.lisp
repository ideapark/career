(setf nums nil)

(dolist (x '(5 8 4 2 1 9 6 7 3))
  (setf nums (bst-insert x nums #'<)))

(bst-find 12 nums #'<)

(bst-find 4 nums #'<)

(bst-min nums)

(bst-max nums)

(setf nums (bst-remove 2 nums #'<))

(bst-find 2 nums #'<)

(bst-traverse #'princ nums)
