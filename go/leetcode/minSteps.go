package main

import "fmt"

func minSteps(n int) int {
	if n == 1 {
		return 0
	}
	countResult := 0
	for i := 2; i <= n; i++ {
		for n%i == 0 {
			// `i` является наименьшим делителем `n`, добавляем `i` операций:
			countResult += i
			n /= i
		}
	}
	return countResult
}

func main() {
	fmt.Println(minSteps(9))
}
