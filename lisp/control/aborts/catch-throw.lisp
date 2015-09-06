(defun super()
  (catch 'abort
    (sub)
    (format t "We'll never see this.")))


(defun sub()
  (throw 'abort 99))
