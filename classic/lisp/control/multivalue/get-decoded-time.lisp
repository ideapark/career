(multiple-value-bind (s m h) (get-decoded-time)
  (format nil "~A:~A:~A" h m s))
