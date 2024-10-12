package main

import (
	"fmt"
	"math"
)
var k,p,v float64 = 1296,6,6
func main() {
	fmt.Println(T())
}

func T() float64 {
	w := W()
	return 6 / w
}

func W() float64 {
	m := M()
	result := math.Sqrt(k / m)
	return result
}

func M() float64 {
	return p * v
}
