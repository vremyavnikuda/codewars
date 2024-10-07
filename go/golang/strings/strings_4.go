package main

import "fmt"

func main() {
	var str string
	fmt.Scanln(&str)
	fmt.Println(indexText(str))
}
func indexText(text string) string {
	var result string

	for i := 0; i < len(text); i++ {
		if i%2 != 0 {
			result += string(text[i])
		}
	}
	return result
}
