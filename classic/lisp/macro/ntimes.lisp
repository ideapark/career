(defmacro ntimes (n &rest body)          ; wrong
  `(do ((x 0 (+ x 1)))
       ((>= x ,n))
     ,@body))


(ntimes 10
  (princ "."))


;;; BUG: inadvertent variable capture.
(let ((x 10))
  (ntimes 5
    (setf x (+ x 1)))
  x)

;; EXPAND TO
(let ((x 10))
  (do ((x 0 (+ x 1)))
       ((>= x 5))
    (setf x (+ x 1)))
  x)
