(dolist (x '(a b c d e))
  (format t "~A " x)
  (if (eql x 'c)
      (return 'done)))
