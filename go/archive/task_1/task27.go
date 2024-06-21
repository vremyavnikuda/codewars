package main

import (
	"fmt"
)

func main() {
	var maxNumber, currentNumber, countMax int

	fmt.Scan(&currentNumber)
	maxNumber = currentNumber
	countMax = 1

	for {
		fmt.Scan(&currentNumber)

		if currentNumber == 0 {
			break
		}

		if currentNumber > maxNumber {
			maxNumber = currentNumber
			countMax = 1
		} else if currentNumber == maxNumber {
			countMax++
		}
	}
	fmt.Println(countMax)
}
