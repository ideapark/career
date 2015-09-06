(defclass rectangle ()
  (height width))


(defclass circle ()
  (radius))


(defmethod area ((x rectangle))
  (* (slot-value x 'height) (slot-value x 'width)))


(defmethod area ((x circle))
  (* pi (expt (slot-value x 'radius) 2)))


(let ((r (make-instance 'rectangle)))
  (setf (slot-value r 'height) 2
        (slot-value r 'width)  3)
  (area r))
