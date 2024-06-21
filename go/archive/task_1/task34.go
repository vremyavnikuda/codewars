package main

import (
	"fmt"
)

func main() {
	var num float64
	fmt.Scan(&num)

	if num <= 0 {
		fmt.Printf("число %.2f не подходит\n", num)
	} else if num > 10000 {
		fmt.Printf("%.6e\n", num)
	} else {
		squared := num * num
		fmt.Printf("%.4f\n", squared)
	}
}
