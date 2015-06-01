(let ((x 10))
  (defun foo ()
    (declare (special x))
    x))

(let ((x 20))
  (declare (special x))
  (foo))
