package main

import "fmt"

func main() {
	x := 3
	switch x {
	case 2:
		x += 1
	case 3:
		x += 1
	case 4:
		x -= 1
	}
	fmt.Println(x)
}
