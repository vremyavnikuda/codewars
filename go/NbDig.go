package main

import (
	"strconv"
	"strings"
)

func main() {}

func NbDig(n int, d int) int {
	k := 0
	result := strconv.Itoa(d)

	for i := k; i <= n; i++ {
		square := i * i
		squareSTR := strconv.Itoa(square)
		k += strings.Count(squareSTR, result)
	}
	return k
}
