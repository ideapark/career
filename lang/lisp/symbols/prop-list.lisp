;; In Common Lisp every symbol has a property-list, or plist
;; The function get takes a symbol and a key of any type,
;; and returns the value associated with that key in the
;; symbol's property list
(get 'alizarin 'color)

;; To associate a value with a key you can use setf with get.
(setf (get 'alizarin 'color) 'red)
(get 'alizarin 'color)

;; The function symbol-plist returns the property list of a
;; symbol.
(setf (get 'alizarin 'transparency) 'high)
(symbol-plist 'alizarin)
