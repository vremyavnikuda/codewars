package main

import "fmt"

func main() {
	array := [3]int{10, 21, 13}
	fmt.Println(Gimme(array))
}
func Gimme(array [3]int) int {
	tempMax := array[0]
	tempMin := array[0]
	for _, elem := range array {
		if elem > tempMax {
			tempMax = elem
		}
		if elem < tempMin {
			tempMin = elem
		}
	}

	for i, e := range array {
		if e != tempMax && e != tempMin {
			return i
		}
	}
	return -1
}
