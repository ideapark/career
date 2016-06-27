(setf ht (make-hash-table))

(gethash 'color ht)

(setf (gethash 'color ht) 'red)

(gethash 'color ht)
