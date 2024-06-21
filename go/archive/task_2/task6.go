package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	count:=0
	array:=make([]int, n )
	for i := 0; i < len(array); i++ {
		fmt.Scan(&array[i])
	}
	
	for i := 0; i < n; i++ {
		if array[i]!=0 {
			continue
		}else{
			count++
		}
	}
	fmt.Print(count)
}
