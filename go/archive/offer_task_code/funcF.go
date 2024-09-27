package main

import "fmt"

func f(text string) {
	fmt.Println(text)
	return
}

func main() {
	var text string
	fmt.Scanln(&text)
	f(text)
}
