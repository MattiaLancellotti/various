#lang racket/gui

(define my-language 'Italian)

(define translations
  #hash([English . "Hello world"]
        [French . "Bonjour le monde"]
        [German . "Hallo Welt"]
        [Spanish . "Hola mundo"]
        [Italian . "Ciao mondo"]))

(define my-hello-world
  (hash-ref translations my-language
            "hello world"))

(message-box "" my-hello-world)
