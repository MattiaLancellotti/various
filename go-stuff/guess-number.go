package main

import (
     "fmt"
     "time"
     "math/rand"
)

// This function takes an integer as the limit of the pseudo-random generation.
func GenerateNumber(limit int) int {
     fmt.Println("Generating a random number between 0 and ", limit)

     // Using the time as seed for the algorithm.
     seed := rand.NewSource(time.Now().UnixNano())
     randObj := rand.New(seed)

     return randObj.Intn(limit)
}

// TODO: Maybe some pretty printing.
func main() {
     // Generating the new number
     number := GenerateNumber(10)

     // Time for the user to guess the number
     var userGuess int
     for {
          fmt.Print("Your turn: ")
          _, err := fmt.Scan(&userGuess)
          if err != nil {
               fmt.Println("Something went wrong while reading user's input.")
          }

          // Checking if the user guessed the number
          if userGuess == number { break }

          fmt.Println("Gotta try again mate!")
     }

     fmt.Println("Nice catch boyo!");
}
