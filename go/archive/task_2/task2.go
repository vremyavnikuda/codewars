package main

import "fmt"

func main() {
	var k int
	fmt.Scan(&k)

	// Calculate hours and minutes
	h := k / 3600
	m := (k % 3600) / 60

	// Print the result
	fmt.Printf("It is %d hours %d minutes.\n", h, m)
}
