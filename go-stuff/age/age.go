package main

import (
     "os"
     "fmt"
     "bufio"
)

func main() {
     var age int

     /* Reading the age */
     fmt.Println("What is your age?")
     _, err := fmt.Scan(&age)
     if err != nil {
          fmt.Println("Coulnd't read your age.")
          os.Exit(1)
     }

     /* Reading your name */
     reader := bufio.NewReader(os.Stdin)
     fmt.Println("What is your name?")
     name, err := reader.ReadString('\n')
     if err != nil {
          fmt.Println("Coulnd't read your name.")
          os.Exit(1)
     }

     /* Outputting */
     fmt.Println("Your name is ", name, " and your age ", age)
}
