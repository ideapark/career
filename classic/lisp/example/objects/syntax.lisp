(defmacro defprop (name &optional meth?)
  '(progn
     (defun ,name (obj &rest args)
       ,(if meth?
            '(run-methods obj ',name args)
            '(rget ',name obj)))
     (defun (setf ,name) (val obj)
       (setf (gethash ',name obj) val))))

(defun run-methods (obj name args)
  (let ((meth (rget name obj)))
    (if meth
        (apply meth obj args)
        (error "No ~A method for ~A." name obj))))
