(tagbody
  (setf x 0)
 top
  (setf x (+ x 1))
  (format t "~A " x)
  (if (< x 10)
      (go top)))
