(defun len (lst)
  (if (null lst)
      0
      (+ (len (cdr lst)) 1)))
