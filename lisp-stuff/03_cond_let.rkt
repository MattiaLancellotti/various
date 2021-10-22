#lang racket

;;; base10->baseN as the name says is a function that converts any given number
;;; from base 10 to base N. The base needs to be more than 1.
(define base10->baseN
  (lambda (number base [range 10]) (cond
                                     ;; If the given base doesn't respect the
                                     ;; given rules throw an error.
                                     [(not (acceptable? base range))
                                      (error "Couldn't accept the given base.")]
                                     [(zero? number) ""]

                                     ;; This is where the new number gets
                                     ;; calculated and composed.
                                     [(string-append
                                        (number->string (remainder number base))
                                        (base10->baseN
                                          (quotient number base) base))])))

;;; Checks if the given base is enough (> 1).
(define acceptable?
  (lambda (base range) (and (> base 1) (<= base range))))

;;; This function takes a string and reverses it.
(define string-reverse
  (lambda (str) (when (non-empty-string? str)
                  ;; Converting the string to a list to use the `reverse`
                  ;; function.
                  (list->string (reverse (string->list str))))))

(string-reverse (base10->baseN 10 6))
