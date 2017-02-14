(defmacro ntimes (n &rest body)     ;wrong
  (let ((g (gensym)))
    `(do ((,g 0 (+ ,g 1)))
         ((>= ,g ,n))
       ,@body)))


(let ((v 10))
  (ntimes (setf v (- v 1))
    (princ ".")))


;;; EXPAND TO
(let ((v 10))
  (do ((#:g1 0 (+ #:g1 1)))
      ((>= #:g1 (setf v (- v 1))))
    (princ ".")))
