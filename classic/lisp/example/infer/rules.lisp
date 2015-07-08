(defvar *rules* (make-hash-table))

(defmacro <- (con &optional ant)
  '(length (push (cons (cdr ',con) ',ant)
                 (gethash (car ',con) *rules*))))
