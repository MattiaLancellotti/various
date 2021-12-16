; A list of functions and things for university
#lang racket

;;; definig a custom pi greco
(define pi-greco 3.14)

;;; Defining an helper function
(define string-extract
  (lambda (s)
    (substring s 0 (- (string-length s) 1))))

;;; Checks if a word is a female word in italian
(define female?
  ;; this piece of code checks whether the last character of a word is an 'a'
  (lambda (s)
    (char=?
      (string-ref s (- (string-length s) 1)) #\a)))

;;; Appending an 'i' at the end of every string
(define plural
  ;; Choosing which letter to attach
  (lambda (s)
    (if (female? s)
      (string-append (string-extract s) "e")
      (string-append (string-extract s) "i"))))

;;; Taking a string and writing it as a private name
(define make-name
  (lambda ([s "name"])
    (string->immutable-string
      (string-titlecase s))))

;;; Calculating a cylinder's total area
(define cylinder
  ;; Creating the lambda to calculate the area
  ;; of a cylinder.
  (lambda (r h) (* 2 pi-greco r (+ r h))))

(cylinder 5.0 11.8)          ; Area of a cylinder
(plural "fiore")             ; "fiore" to "fiori"
(female? "amica")            ; Checks if the given word is a female word
(make-name "mattia")         ; Title-casing
(make-name)                  ; Testing default values
