#lang racket

(define net-mask-c "11000000")
(define handshake  "10101010")
(define inet-loopb "01111111")

;;; 0 <-> 1
(define opposite
  (lambda (digit) (if (string=? digit "1") "0" "1")))

;;; Recursive 1's complement 
;;; This function will recursively iterate through the given string of digits
;;; until it gets to a single digit to then return the opposite.
(define complement-one
  (lambda (binary) (if (= (string-length binary) 1)
                     ;; If the passed binary number is composed by just one
                     ;; digit there is no need to do further operation other
                     ;; than switching this single digit.
                     (opposite binary)

                     ;;; Otherwise get the first available digit, switch it and
                     ;;; append it to the remaining digits. (recursively)
                     (string-append 
                       (opposite (substring binary 0 1))
                       (complement-one (substring binary 1))))))

;;; Recursive 1's complement
;;; This version doas the exact same thing as the previous algorithm but from
;;; the far right of the string to the left. The only difference in the result
;;; is that the evaluated string will be reversed (check the comments before
;;; string-append).
(define complement-one-reverse
  (lambda (binary) (let ((len (string-length binary)))
                     (if (= len 1)
                       ;; If the length of the binary number is 1 then proceeds
                       ;; changing it.
                       (opposite binary)

                       ;; Otherwise keep iterating the string from right to
                       ;; left. Keep in mind that this method will print the
                       ;; inverse of the binary string.
                       ;;
                       ;; For instance the string "0010" will be transformed in
                       ;; "1011" and not "1101".
                       (string-append
                         (opposite (substring binary (- len 1)))
                         (complement-one-reverse
                           (substring binary 0 (- len 1))))))))

;;; Recursive 1's complement (2nd version)
;;; This function will do the same thing as the previous version but instead of
;;; using substring to isolate a single digit recursion after recursion, this
;;; will isolate half of the string.
(define complement-one2
  (lambda (binary) (let ((len (string-length binary)))
                     (if (= len 1)
                       ;; If the passed string is already a single character the
                       ;; only thing needed here is to find the opposite.
                       (opposite binary)
                     
                       ;; Defining the length of the divided string
                       (let ((div (quotient len 2)))
                         ;; Continues by dividing the string in half
                         (string-append 
                           (complement-one2 (substring binary 0 div))
                           (complement-one2 (substring binary   div))))))))

(printf "1: Calculating 1's complement of ~a: ~s~%"
        net-mask-c (complement-one net-mask-c))

(printf "2: Calculating 1's complement of ~a: ~s~%"
        handshake  (complement-one2 handshake))

(printf "3: Calculating 1's complement of ~a: ~s~%"
        inet-loopb (complement-one-reverse inet-loopb))
