package main

import "fmt"

func main() {
	var b, s int
	fmt.Scan(&b, &s)

	sum := 0
	for i := b; i <= s; i++ {
		sum += i
	}
	fmt.Println(sum)
}
