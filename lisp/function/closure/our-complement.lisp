(defun our-complement (f)
  #'(lambda (&rest args)
      (not (apply f args))))
