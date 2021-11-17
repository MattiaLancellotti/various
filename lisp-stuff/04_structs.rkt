#lang racket

(struct person (FirstName SecondName Age)
  #:guard (lambda (FirstName SecondName Age name)
            (unless (and (positive? Age) (real? Age))
              (error "The age must be strictly positive."))
            (values FirstName SecondName Age)))

(define Jesus (person "Jesus" "Christ" 33))
(define God (person "God" "" +inf.0))
