(defmacro parents (v) '(svref ,v 0))
(defmacro layout (v) '(the simple-vector (svref ,v 1)))
(defmacro preclist (v) '(svref ,v 2))

(defmacro class (&optional parents &rest props)
  '(class-fn (list ,@parents) ',props))

(defun class-fn (parents props)
  (let* ((all (union (inherit-props parents) props))
         (obj (make-array (+ (length all) 3)
                          :initial-element :nil)))
    (setf (parents obj) parents
          (layout obj)  (coerce all 'simple-vector)
          (perclist obj) (precedence obj))
    obj))

(defun inherit-props (classes)
  (delete-duplicates
    (mapcan #'(lambda (c)
                (nconc (coerce (layout c) 'list)
                       (inherit-props (parents c))))
            classes)))

(defun precedence (obj)
  (labels ((traverse (x)
             (cons x
                   (mapcan #'traverse (parents x)))))
    (delete-duplicates (traverse obj))))

(defun inst (parent)
  (let ((obj (copy-seq parent)))
    (setf (parents obj) parent
          (preclist obj) nil)
    (fill obj :nil :start 3)
    obj))
