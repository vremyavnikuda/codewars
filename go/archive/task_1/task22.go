package main

import (
	"fmt"
	"strconv"
)

func main() {
	var num int
	fmt.Scan(&num)

	numLacky := strconv.Itoa(num)

	num1 := numLacky[0] + numLacky[1] + numLacky[2]
	num2 := numLacky[3] + numLacky[4] + numLacky[5]

	if num1 == num2 {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
