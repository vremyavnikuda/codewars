package main

import (
	"fmt"
)

func main() {
	var a string
	fmt.Scan(&a)

	rs := []rune(a)

	if len(a) == len(rs) && len(rs) >= 5 {
		z := true
		for _, symb := range rs {
			if !isLetterOrDigit(symb) {
				z = false
				break
			}
		}

		if z {
			fmt.Println("Ok")
		} else {
			fmt.Println("Wrong password")
		}
	} else {
		fmt.Println("Wrong password")
	}
}

func isLetterOrDigit(r rune) bool {
	return (r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z') || (r >= '0' && r <= '9')
}
