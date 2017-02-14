(defstruct point
  x
  y)

(setf p (make-point :x 0 :y 0))

(point-x p)

(setf (point-y p) 2)

(print p)

(point-p p)

(typep p 'point)
