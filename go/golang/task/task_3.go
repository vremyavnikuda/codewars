package main

import "fmt"

func main() {
	var seconds int
	fmt.Scan(&seconds)

	hours := seconds / 3600
	minutes := (seconds % 3600) / 60

	fmt.Printf("It is %d hours %d minutes.\n", hours, minutes)
}
