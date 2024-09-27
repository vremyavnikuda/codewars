package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

func main() {
	text, _ := bufio.NewReader(os.Stdin).ReadString('\n')

	text = strings.TrimSpace(text)

	if isValidString(text) {
		fmt.Println("Right")
	} else {
		fmt.Println("Wrong")
	}
}

func isValidString(str string) bool {
	if len(str) == 0 {
		return false
	}

	runes := []rune(str)

	if !unicode.IsUpper(runes[0]) || runes[len(runes)-1] != '.' {
		return false
	}

	return true
}
