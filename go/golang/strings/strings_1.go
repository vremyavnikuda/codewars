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
	//delete last symbol new string
	text = strings.TrimSpace(text)

	if len(text) > 0 && unicode.IsUpper([]rune(text)[0]) && text[len(text)-1] == '.' {
		fmt.Println("Right")
	} else {
		fmt.Println("Wrong")
	}
}
