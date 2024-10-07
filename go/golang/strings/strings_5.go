package main

import (
	"fmt"
	"strings"
)

func main() {
	var str string
	fmt.Scanln(&str)
	result := str

	for _, elem := range result {
		if strings.Count(str, string(elem)) > 1 {
			result = strings.ReplaceAll(result, string(elem), "")
		}
	}
	fmt.Println(result)
}
