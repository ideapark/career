(defun compress (x)
  (if (consp x)
      (compr (car x) 1 (cdr x))
      x))


(defun compr (e n lst)
  (if (null lst)
      (list (n-elts e n))
      (let ((next (car lst)))
        (if (eql next e)
            (compr e (+ n 1) (cdr lst))
            (cons (n-elts e n)
                  (compr next 1 (cdr lst)))))))


(defun n-elts (e n)
  (if (> n 1)
      (list n e)
      e))


(defun uncompress (lst)
  (if (null lst)
      nil
      (let ((e (car lst))
            (r(uncompress (cdr lst))))
        (if (consp e)
            (append (apply #'list-of e)
                    r)
            (cons e r)))))


(defun list-of (n e)
  (if (zerop n)
      nil
      (cons e (list-of (- n 1) e))))
