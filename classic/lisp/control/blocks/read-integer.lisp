(defun read-integer (str)
  (let ((accum 0))
    (dotimes (pos (length str))
      (let ((i (digit-char-p (char str pos))))
        (if i
            (setf accum (t (* accum 10) i))
            (return-from read-integer nil))))
    accum))
