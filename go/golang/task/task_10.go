package main

import (
	"fmt"
)

func main() {
	var a, b, result int
	flag := false
	fmt.Scanln(&a)
	fmt.Scanln(&b)
	for i := a; i <= b; i++ {
		if i%7 == 0 {
			flag = true
			result = i
		}
	}
	if flag {
		fmt.Println(result)
	} else {
		fmt.Println("NO")
	}
}
