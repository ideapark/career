;;;; Lisp Lists

;; flowers
'(rose violet daisy buttercup)

;; flowers (exactly the same with above)
'(rose
  violet
  daisy
  buttercup)

;; numbeers
(+ 2 2)

;; list inside of list
'(this list has (a list inside of it))

;; atom
2        ; numbeer
"lisp"   ; string
?c       ; char
t        ; true
nil      ; nil (false, empty, ...)

'(this list includes "text between quotation marks.")

;; error message
(this list includes "text between quotation marks.") ;; C-x C-e
;;
;; Debugger entered--Lisp error: (void-function this)
;;   (this list includes "text between quotation marks.")
;;   eval((this list includes "text between quotation marks.") nil)
;;   elisp--eval-last-sexp(nil)
;;   eval-last-sexp(nil)
;;   funcall-interactively(eval-last-sexp nil)
;;   call-interactively(eval-last-sexp nil nil)
;;   command-execute(eval-last-sexp)

;; this is an emacs lisp atom (vector)
[this list includes "text between quotation marks."] ;; C-x C-e


;;; Symbol:
;;;
;;; the universal emacs object (value, function, etc) abstracted representation.
;;;
(symbolp         'deactivate-mark)
(symbol-name     'deactivate-mark)
(symbol-function 'deactivate-mark) ;; symbol can hold function
(symbol-value    'deactivate-mark) ;; and value simultaneously

;; symbol with values
(symbol-value 'kill-ring)
kill-ring

(symbol-value 'fill-column)
fill-column

+   ;; expected value
(+) ;; expected function

;;;; Arguments
(concat "abc" "def")           ;; two atom string
(substring "你好，世界！" 3 5)   ;; 1 atom string, 2 atom numbers
(+ 2 fill-column)              ;; symbol evaluate to value: (eval fill-column)
(concat "The "
	(number-to-string (+ 2 fill-column))
	" red foxes.")         ;; list argument that returns a value

;;; Wrong type argument
;; Debugger entered--Lisp error: (wrong-type-argument number-or-marker-p emacs)
;;   +(2 emacs)
;;   eval((+ 2 'emacs) nil)
;;   elisp--eval-last-sexp(nil)
;;   eval-last-sexp(nil)
;;   funcall-interactively(eval-last-sexp nil)
;;   call-interactively(eval-last-sexp nil nil)
;;   command-execute(eval-last-sexp)
(+ 2 'emacs)

;;;; message
(message "This message appears in the echo area!")
(message "The name of this buffer is: %s." (buffer-name))
(message "The value of fill-column is %d." fill-column)
(message "There are %d %s in the office!"
	 (- fill-column 14)
	 "pink elephants")
(message "He saw %d %s"
	 (- fill-column 32)
	 (concat "red "
		 (substring
		  "The quick brown foxes jumped." 16 21)
		 " leaping."))

;;;; Setting the value of a variable
(set 'flowers '(rose violet daisy buttercup))
(setq flowers '(rose violet daisy buttercup))

(setq carnivores '(lion tiger leopard))
(setq trees '(pine fir oak maple)
      herbivores '(gazellle antelope zebra))

;;;;; Summary

;; Lisp programs are made up of expressions, which are lists or single
;; atoms.
;;
;; Lists are made up of zero or more atoms or inner lists, separated
;; by whitespace and surrounded by parentheses. A list can be empty.
;;
;; Atoms are multi-character symbols, like forward-paragraph, single
;; character symbols like +, strings of characters between double
;; quotation marks, or numbers.
;;
;; A number evaluates to itself.
;;
;; A string between double quotes also evaluates to itself.
;;
;; When you evaluate a symbol by itself, its value is returned.
;;
;; When you evaluate a list, the Lisp interpreter looks at the first
;; symbol in the list and then at the function definition bound to
;; that symbol. Then the instructions in the function definition are
;; carried out.
;;
;; A single-quote ‘'’ tells the Lisp interpreter that it should return
;; the following expression as written, and not evaluate it as it
;; would if the quote were not there.
;;
;; Arguments are the information passed to a function. The arguments
;; to a function are computed by evaluating the rest of the elements
;; of the list of which the function is the first element.
;;
;; A function always returns a value when it is evaluated (unless it
;; gets an error); in addition, it may also carry out some action that
;; is a side effect. In many cases, a function’s primary purpose is to
;; create a side effect.
