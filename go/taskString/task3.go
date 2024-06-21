package main

import (
	"fmt"
	"strings"
)

func main() {
	var firtsWord, lastWord string
	fmt.Scanln(&firtsWord)
	fmt.Scanln(&lastWord)
	fmt.Println(searchWord(firtsWord, lastWord))
}

func searchWord(str1 string, str2 string) int {
	index := strings.Index(str1, str2)
	return index
}
