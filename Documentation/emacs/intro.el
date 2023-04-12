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
(symbolp         'emacs-lisp-mode)
(symbol-name     'emacs-lisp-mode)
(symbol-function 'emacs-lisp-mode)

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
