package main

import (
	"fmt"
)

func main() {
	var str string
	fmt.Scanln(&str)
	fmt.Println(oddFunc(str))
}

func oddFunc(str string) string {
	var result string

	for i := 0; i < len(str); i++ {
		if i%2 != 0 {
			result += string(str[i])
		}
	}
	return result
}
