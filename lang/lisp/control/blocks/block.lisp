(block head
  (format t "Here we go.")
  (return-from head 'idea)
  (format t "We'll never see this."))
