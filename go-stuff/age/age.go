package main

import (
     "os"
     "fmt"
     "strconv"
)

/* A struct rappresentation of a person */
type Person struct {
     FirstName  string
     SecondName string
     Age        int
}

func CreatePerson(FName string, SName string, Age int) *Person {
     person := Person{FName, SName, Age}
     return &person
}

func PrintPerson(person *Person) {
     fmt.Println(person.FirstName,  "\t",
                 person.SecondName, "\t",
                 person.Age)
}

func SavePerson(person *Person) {
     file, err := os.OpenFile(person.FirstName, os.O_WRONLY|os.O_CREATE, 0755)
     if err != nil {
          panic("Couldn't work with files")
     }

     file.WriteString("Name: " + person.FirstName)
     file.WriteString("\nSurname: " + person.SecondName)
     file.WriteString("\nAge: " + strconv.Itoa(person.Age))

     defer file.Close()
}

func main() {
     var (
          fname     string
          sname     string
          age       string
          people [2]*Person
     )

     for i:=0; i<2; i++ {
          fmt.Print("Insert the name: ")
          if _, err := fmt.Scan(&fname); err != nil {
               panic("Couldn't read the name.")
          }

          fmt.Print("Insert the surname: ")
          if _, err := fmt.Scan(&sname); err != nil {
               panic("Couldn't read the surname.")
          }

          fmt.Print("Insert the age: ")
          _, err := fmt.Scan(&age)
          num, nrr := strconv.Atoi(age)
          if err != nil || nrr != nil || num <= 0 {
               panic("Couldn't read the age.")
          }

          people[i] = CreatePerson(fname, sname, num)
     }

     fmt.Println("Name\tSurname\tAge")
     for i:=0; i<2; i++ {
          PrintPerson(people[i])
     }

     fmt.Println("Saving first person in the list.")
     SavePerson(people[1])
}
