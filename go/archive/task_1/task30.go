package main

import "fmt"

func main() {
	var a int
	for {
		_, err := fmt.Scan(&a)
		if err != nil {
			break
		}
		if a < 10 {
			continue
		}
		if a > 100 {
			break
		}
		fmt.Println(a)
	}
}
