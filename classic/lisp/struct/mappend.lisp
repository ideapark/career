(defun mappend (fn &rest lsts)
  (apply #'append (apply #'mapcar fn lsts)))
