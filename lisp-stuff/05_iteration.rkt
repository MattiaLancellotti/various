#lang racket

(define numbers '( 0 1 2 3 ))
(define letters '( a b c d ))

;;; for i in numbers; do display i
(for ([i numbers]) (display i))

(define alphabet0
  (for/hash ([i numbers]
             [j letters])
    (values i j)))

(define alphabet1
  (for/list ([i numbers]
             [j letters])
    '(i j)))

(displayln alphabet0)
(displayln alphabet1)
