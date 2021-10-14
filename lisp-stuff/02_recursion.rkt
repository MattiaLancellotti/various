#lang racket

(define number "10001000")

;;; 0 <-> 1
(define opposite
  (lambda (digit) (if (string=? digit "1") "0" "1")))

;;; Recusrive 1's complement 
(define complement-one
  (lambda (binary) (if (= (string-length binary) 1)
                     ;; If the passed binary number is composed by just one
                     ;; digit there is no need to do further operation other
                     ;; than switching this single digit.
                     (opposite (substring binary 0 1))

                     ;;; Otherwise get the first available digit, switch it and
                     ;;; append it to the remaining digits. (recursively)
                     (string-append 
                       (opposite (substring binary 0 1))
                       (complement-one (substring binary 1))))))

(printf "Calculating 1's complement of ~a: ~s~%"
        number (complement-one "10001000"))
