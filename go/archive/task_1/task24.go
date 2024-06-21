package main

import "fmt"

func main() {
	var i int
	fmt.Scan(&i)

	for i := 1; i <= 10; i++ {
		fmt.Println(i * i)
	}
}
