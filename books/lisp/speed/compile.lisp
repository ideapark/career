(declaim (inline single?))

(defun single? (lst)
  (and (consp lst) (null (cdr lst))))

(defun foo (x)
  (single? (bar x)))
