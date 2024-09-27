package main

import (
	"fmt"
)

func stringToInt(str string) int {
	var num int
	fmt.Sscanf(str, "%d", &num)
	return num
}
