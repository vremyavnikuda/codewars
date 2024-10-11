package main

import (
	"fmt"
	"strconv"
)

func main() {
	var str string
	fmt.Scan(&str)
	fmt.Println(sqrtResult(str))
}

func sqrtResult(str string) string {
	resultElem := ""
	for _, elem := range str {
		num, err := strconv.Atoi(string(elem))
		if err != nil {
			continue
		}
		square := num * num
		resultElem += strconv.Itoa(square)
	}
	return resultElem
}
