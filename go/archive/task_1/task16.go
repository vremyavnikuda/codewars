package main

import (
	"fmt"
)

const (
	a = iota + 1
	_
	b
	c
	d = c + 2
	t
	i
	i2 = iota + 2
)

func main() {
	fmt.Println(i2)
}
