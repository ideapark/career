;;; Lisp Lists

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


