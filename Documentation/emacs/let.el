;; let Expression
(let ((zebra "stripes")
      (tiger "fierce"))
  (message "One kind of animal has %s and another is %s."
	   zebra
	   tiger))

;; vars bind to nil if no initial value specified
(let ((birch 3)
      pine
      fir
      (oak 'some))
  (message "Here are %d variables with %s, %s, and %s value."
	   birch pine fir oak))

(defun type-of-animal (characteritic)
  "Print message in echo area depending on CHARACTERITIC.
If the CHARACTERITIC is the string \"fierce\", then warn of a tiger."
  (if (equal characteritic "fierce")
      (message "It is dangerous!")
    (message "It is lovely.")))

(type-of-animal "fierce")
(type-of-animal "stripes")


