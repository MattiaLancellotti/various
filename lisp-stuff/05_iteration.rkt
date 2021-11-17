#lang racket

(define numbers '( 0 1 2 3 ))
(define letters '( a b c d ))

;;; for i in numbers; do display i
(for ([i numbers]) (display i))

(define alphabet
  (for/hash ([i numbers]
             [j letters])
    (values i j)))
(display alphabet)
