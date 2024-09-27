package main

import "fmt"

func main() {
	menu := map[string]float64{
		"soup":           2.45,
		"pie":            7.99,
		"salat":          6.99,
		"toffee pudding": 3.55,
	}

	fmt.Println(menu)
	fmt.Println(menu["pie"])

	for k, v := range menu {
		fmt.Println(k, v)
	}
}
