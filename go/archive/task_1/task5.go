package main

import "fmt"

func main() {
	println(5 <= 7 && 5 != 7)
	println(7 >= 4 || 5 == 9)
	println(!(7 >= 4) && 5 == 5)
	println(!(11 > 3 || 7 != 4))
	println(10 > 7 && 5 < 6 || 5 == 6)
	sum()
	sum1()
	sum2()
	task0()
}

func sum() {
	x := 5
	y := x + 3
	x -= y
	x++
	println(x)
}

func sum1() {
	var x, y int
	fmt.Scan(&x, &y)
	println(x + y)
}

func sum2() {
	var x, y, z int
	fmt.Scan(&x, &y, &z)
	print(x + y + z)
}

func sum3() {
	var x, y, z int
	fmt.Scanln(&x, &y, &z)
	print(x + y + z)
}

func task0() {
	if x := 33; x%2 == 1 {
		fmt.Println(x + 9)
	} else {
		println(x - 3)
	}
}
