package main

func SquareSum(numbers []int) int {
	sum := 0

	for i := 0; i < len(numbers); i++ {
		sum += numbers[i] * numbers[i]
	}
	return sum
}

func main() {
	println(SquareSum([]int{1, 2, 2}))
}
