#lang scribble/base

@; Generate a PDF or HTML document
@(require (only-in racket ~a))
@(define N 99)
@title{Bottles: @italic{Abridged}}
@(apply
  itemlist
  (for/list ([n (in-range N 0 -1)])
    @item{@(~a n) bottles.}))
