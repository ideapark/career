(setf path (make-pathname :name "myfile"))
(with-open-file (str path :direction :output
                          :if-exists :supersede)
  (format str "Something~%"))
