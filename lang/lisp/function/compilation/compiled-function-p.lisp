(defun foo (x)
  (+ x 1))

(compiled-function-p #'foo)

(compile 'foo)
