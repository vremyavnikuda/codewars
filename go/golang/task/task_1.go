package main

import "fmt"

func main() {
	var number int
	sum := 0
	fmt.Scan(&number)
	for number > 0 {
		lastDigit := number % 10
		sum += lastDigit
		number = number / 10
	}
	fmt.Println(sum)
}

//func main(){
//	var a,b,c int
//	Scanf("%1d%1d%1d",&a,&b,&c)
//	Print(c+b+a)
//}
