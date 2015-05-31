(defun make-adder (n)
  #'(lambda (x)
      (+ x n)))
