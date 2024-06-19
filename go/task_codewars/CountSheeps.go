package main

import "fmt"

// CountSheeps /*Function count sum true*/
func CountSheeps(numbers []bool) int {
	if len(numbers) == 0 {
		return 0
	}
	count := 0
	for i := 0; i < len(numbers); i++ {
		if numbers[i] == true {
			count++
		} else {
			continue
		}
	}
	return count
}

func main() {
	var numbers []bool = []bool{
		true, true, true, false,
		true, true, true, true,
		true, false, true, false,
		true, false, false, true,
		true, true, true, true,
		false, false, true, true,
	}
	fmt.Println(CountSheeps(numbers))
	println(CountSheeps1(numbers))
}

// CountSheeps1 /*offer function realization*/
func CountSheeps1(numbers []bool) int {
	sum := 0
	for _, x := range numbers {
		if x {
			sum += 1
		}
	}
	return sum
}
