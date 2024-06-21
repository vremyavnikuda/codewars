package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	
	result := printNumbers(n)
	for _,num:=range result{
		fmt.Print(num," ")
	}
	fmt.Println()
}

func printNumbers(n int )[]int {
	var result []int
	
	power:=1
	
	for power <=n{
		result = append(result, power)
		power*=2
	}
	return result
}