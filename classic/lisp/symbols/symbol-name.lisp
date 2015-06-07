(symbol-name 'abc)

;; symbol name include witespace
(symbol-name '|a b c|)
(list '|Lisp 1.5| '|| '|abc| '|ABC|)

;; case-insensitive
(eql 'aBc 'Abc)
(CaR '(a b c))
