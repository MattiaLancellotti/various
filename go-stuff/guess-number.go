package main

import (
     "fmt"
     "time"
     "math/rand"
)

func main() {
     // Parsing milliseconds
     m, err := time.ParseDuration("2s")
     if err != nil {
          fmt.Println("An error has occurred while parsing time.")
     }

     // Waiting m seconds
     fmt.Println("Now choosing a number ")
     time.Sleep(m)

     // Choosing the random number
     s1 := rand.NewSource(time.Now().UnixNano())
     r1 := rand.New(s1)
     num := r1.Intn(10)

     // Time for the user to guess the number
     var userGuess int
     for {
          fmt.Print("Your turn: ")
          _, err = fmt.Scan(&userGuess)
          if err != nil {
               fmt.Println("Something went wrong while reading user's input.")
          }

          // Checking if the user guessed the number
          if userGuess == num { break }

          fmt.Println("Gotta try again mate!")
     }

     fmt.Println("Nice catch boyo!");
}
