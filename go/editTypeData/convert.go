package main

import "fmt"

func main() {
	a := 101.0 / 2.0
	fmt.Println(a + float64(uint8(a)))
}

func convert(x int64) uint16 {
	return uint16(x)
}
