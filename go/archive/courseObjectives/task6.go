package main

import (
	"fmt"
	"math"
)

var k, p, v float64

func main() {
	k = 25.0
	p = 3.0
	v = 2.0

	// Вызываем функцию T и выводим результат
	result := T()
	fmt.Println("Результат функции T:", result)
}

func T() float64 {
	w := W()
	t := 6 / w
	return t
}

func W() float64 {
	m := M()
	w := math.Sqrt(k / m)
	return w
}

func M() float64 {
	m := p * v
	return m
}
