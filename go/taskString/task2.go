package main

import "fmt"

func main() {
	var str string
	fmt.Scanln(&str)
	if Polindrome(str) {
		fmt.Println("Палиндром")
	} else {
		fmt.Println("Нет")
	}
}

func Polindrome(str string) bool {
	if len(str) == 0 {
		return false
	}

	runes := []rune(str)

	//палиндром
	for i := 0; i < len(runes)/2; i++ {
		if runes[i] != runes[len(runes)-i-1] {
			return false
		}
	}
	return true
}
