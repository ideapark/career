(multiple-value-bind (x y z) (values 1 2 3)
  (list x y z))

(multiple-value-bind (x y z) (values 1 2)
  (list x y z))
