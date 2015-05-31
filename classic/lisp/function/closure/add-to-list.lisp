(defun add-to-list (num lst)
  (mapcar #'(lambda (x)
              (+ x num))
          lst))
