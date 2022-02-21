;;
;; Huffman Encoding Tree
;;

;; Why:
;;
;; If all our messages are made up of the enght symbols and we choose
;; a code with tree bits per character:
;;
;;   (A 000)  (C 010)  (E 100)  (G 110)
;;   (B 001)  (D 011)  (F 101)  (H 111)
;;
;; Then, the message:
;;
;;   BACADAEAFABBAAAGAH
;;
;; will be encoded as the string of 54 bits:
;;
;;   001000010000011000100000101000001001000000000110000111
;;
;; Codes such as ASCII and the A-through-H code above are known as
;; fixed-length codes, because they represent each symbol in the
;; message with the same number of bits. It is sometimes advantageous
;; to use variable-length codes, in which different symbols may be
;; represented by different numbers of bits. For example, Morse code
;; does not use the same number of dots and dashes for each letter of
;; the alphabet. In particular, E, the most frequent letter, is
;; represented by a single dot. In general, if our messages are such
;; that some symbols appear very frequently and some very rarely, we
;; can encode data more efficiently (i.e., using fewer bits per
;; message) if we assign shorter codes to the frequent
;; symbols. Consider the following alternative code for the letters A
;; through H:
;;
;;   (A    0)  (C 1010)  (E 1100)  (G 1110)
;;   (B  100)  (D 1011)  (F 1101)  (H 1111)
;;
;; With this code, the same mesage as above is encoded as the string
;;
;;   100010100101101100011010100100000111001111
;;
;; This string contains 42 bits, so it saves more than 20% in space in
;; comparison with the fixed-length code shown above.

;; HowTo:
;;
;; The algorithm for generating a Huffman tree is very simple. The
;; idea is to arrange the tree so that the symbols with the lowest
;; frequency appear farthest away from the root. Begin with the set of
;; leaf nodes, containing symbols and their frequencies, as determined
;; by the initial data from which the code is to be constructed. Now
;; find two leaves with the lowest weights and merge them to produce a
;; node that has these two nodes as its left and right branches. The
;; weight of the new node is the sum of the two weights. Remove the
;; two leaves from the original set and replace them by this new
;; node. Now continue this process. At each step, merge two nodes with
;; the smallest weights, removing them from the set and replacing them
;; with a node that has these two as its left and right branches. The
;; process stops when there is only one node left, which is the root
;; of the entire tree.
;;
;;   Start  [(A 8) (B 3) (C 1) (D 1) (E 1) (F 1) (G 1) (H 1)]
;;   Merge  [(A 8) (B 3) ({C D} 2) (E 1) (F 1) (G 1) (H 1)  ]
;;   Merge  [(A 8) (B 3) ({C D} 2) ({E F} 2) (G 1) (H 1)    ]
;;   Merge  [(A 8) (B 3) ({C D} 2) ({E F} 2) ({G H} 2)      ]
;;   Merge  [(A 8) (B 3) ({C D} 2) ({E F G H} 4)            ]
;;   Merge  [(A 8) ({B C D} 5) ({E F G H} 4)                ]
;;   Merge  [(A 8) ({B C D E F G H} 9)                      ]
;;   Final  [({A B C D E F G H} 17)                         ]

;;
;; Implementation:
;;

;; representing huffman tree
(define (make-leaf symbol weight)
  (list 'leaf symbol weight))

(define (leaf? object)
  (eq? (car object) 'leaf))

(define (symbol-leaf x) (cadr x))

(define (weight-leaf x) (caddr x))

(define (make-code-tree left right)
  (list left
        right
        (append (symbols left) (symbols right))
        (+ (weight left) (weight right))))

(define (left-branch tree) (car tree))

(define (right-branch tree) (cadr tree))

(define (symbols tree)
  (if (leaf? tree)
      (list (symbol-leaf tree))
      (caddr tree)))

(define (weight tree)
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))

;; the decoding procedure
(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
        '()
        (let ((next-branch (choose-branch (car bits) current-branch)))
          (if (leaf? next-branch)
              (cons (symbol-leaf next-branch)
                    (decode-1 (cdr bits) tree))
              (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))

(define (choose-branch bit branch)
  (cond ((= bit 0) (left-branch branch))
        ((= bit 1) (right-branch branch))
        (else (error "bad bit -- CHOOSE-BRANCH" bit))))
