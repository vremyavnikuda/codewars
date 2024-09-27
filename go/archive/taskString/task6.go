package main

import (
	"fmt"
	"unicode"
)

func main() {
	var args string
	fmt.Scanln(&args)
	if passwordConfirmation(args) {
		fmt.Println("Ok")
	} else {
		fmt.Println("Wrong password")
	}
}

func passwordConfirmation(password string) bool {
	//проверяем длину пароля
	if len(password) < 5 {
		return false
	}

	//проверяем наличие букв латинского алфавита, кириллических символов и арабских цифр
	for _, char := range password {
		if !unicode.IsDigit(char) && !unicode.IsLetter(char) && !unicode.Is(unicode.Latin, char) && unicode.Is(unicode.Cyrillic, char) {
			return false
		}
	}
	return true
}
