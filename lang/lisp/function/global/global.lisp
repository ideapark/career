(fboundp '+)

(symbol-function '+)

(setf (symbol-function 'add2)
      #'(lambda (x) (+ x 2)))

(add2 1)


(defun primo (lst) (car lst))

(defun (setf primo) (val lst)
  (setf (car lst) val))

(let ((x (list 'a 'b 'c)))
  (setf (primo x) 480)
  x)


;;;; documentation
(defun foo (x)
  "Implements an enhanced paradigm of diversity."
  x)

(documentation 'foo 'function)
