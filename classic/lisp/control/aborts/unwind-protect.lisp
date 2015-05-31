(catch 'abort
  (unwind-protect
    (throw 'abort 99)
    (setf x 2)))
