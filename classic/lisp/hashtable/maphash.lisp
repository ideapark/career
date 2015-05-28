(setf ht (make-hash-table))

(setf (gethash 'shape ht) 'spherical
      (gethash 'size  ht) 'giant)

(maphash #'(lambda (k v)
             (format t "~A = ~A~%" k v))
         ht)
