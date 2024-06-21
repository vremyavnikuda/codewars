package main

import (
	"fmt"
	"strconv"
)

func main() {
	var input string
	fmt.Scan(&input)
	number, _ := strconv.Atoi(input)
	sum := number / 100 + number%100/10 + number%10
	fmt.Println(sum)
}
