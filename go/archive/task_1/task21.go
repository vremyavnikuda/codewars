package main

import (
	"fmt"
	"strconv"
)

func main() {
	var num int
	fmt.Scan(&num)
	s := strconv.Itoa(num)

	fmt.Println(s[0:1])
}
