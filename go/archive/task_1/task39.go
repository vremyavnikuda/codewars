package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	
	array:=make([]int ,n)
	var sum int
	
	for i:=0;i<n;i++{
		fmt.Scan(&array[i])
	}
	
	for i:=0;i<n;i++{
		if array[i]>=0{
			sum++
		}
	}
	fmt.Println(sum)
}