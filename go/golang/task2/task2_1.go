package main

import (
	"fmt"
	"strings"
)

func main() {
	var str string
	fmt.Scan(&str)
	fmt.Println(formatSTR(str))
}

func formatSTR(str string) string {
	joined := strings.Join(strings.Split(str, ""), "*")
	return joined
}