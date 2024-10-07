package main

import "fmt"

func main() {
	var text string
	fmt.Scanln(&text)
	if palindrom(text) {
		fmt.Println("Палиндром")
	} else {
		fmt.Println("Нет")
	}
}

func palindrom(s string) bool {
	if len(s) == 0 {
		return false
	}

	text := []rune(s)

	for i := 0; i < len(text)/2; i++ {
		if text[i] != text[len(text)-i-1] {
			return false
		}
	}
	return true
}
