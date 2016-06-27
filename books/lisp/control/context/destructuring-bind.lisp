(destructuring-bind (w (x y) . z) '(a (b c) d e)
  (list w x y z))
