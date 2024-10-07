package main

import (
	"fmt"
	"strings"
)

func main() {
	var text, word string
	fmt.Scanln(&text)
	fmt.Scanln(&word)
	fmt.Println(searchWord(text, word))

}

func searchWord(text string, word string) int {
	index := strings.Index(text, word)
	return index
}
