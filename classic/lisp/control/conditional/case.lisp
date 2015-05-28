(defun month-length (mon)
  (case mon
    ((jan mar may jul aug oct dec) 31)
    ((apr jun sept nov) 30)
    (feb
      (if (leap-year)
          29
          28))
    (otherwise "unknown month")))
