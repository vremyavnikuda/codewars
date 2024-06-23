package main

import (
	"fmt"
	"math"
)

func main() {
	var a, b int
	fmt.Scanln(&a, &b)
	fmt.Println(lengthHypotenuse(a, b))
}

func lengthHypotenuse(a int, b int) int {
	result := int(math.Sqrt(float64((a * a) + (b * b))))
	return result
}
