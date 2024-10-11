package main

import (
	"fmt"
	"math"
)

func main() {
	var a, b int
	fmt.Scan(&a, &b)
	fmt.Println(result(a, b))

}

func result(a int, b int) int {
	var fmt_result int
	if a != 0 && b != 0 {
		fmt_result = (a * a) + (b * b)
	}
	return int(math.Sqrt(float64(fmt_result)))
}
