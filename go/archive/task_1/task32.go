package main

import "fmt"

type Person struct {
	Name string
}

func (p Person) Talk() string {
	fmt.Println("Hi, my name is", p.Name)
	return p.Name
}

func main() {
	// Создаем объект типа Person с именем Andrew
	person := Person{Name: "Andrew"}

	person.Talk()
}
