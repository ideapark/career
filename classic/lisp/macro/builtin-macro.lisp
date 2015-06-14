(pprint (macroexpand-1 `(cond (a b)
                              (c d e)
                              (t f))))

;; (IF A
;;     B
;;     (IF C
;;         (PROGN D E)
;;         F))
