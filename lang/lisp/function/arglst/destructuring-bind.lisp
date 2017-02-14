(destructuring-bind ((&key w x) &rest y) '((:w 3) a)
  (list w x y))
