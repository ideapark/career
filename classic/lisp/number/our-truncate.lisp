(defun our-truncate (n)
  (if (> n 0)
      (floor n)
      (ceiling n)))
