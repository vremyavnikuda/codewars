package main

import "fmt"

func main(){
	var a int
	_,err:=fmt.Scan(&a)
	if err!=nil{
		fmt.Println(a+1)
	}else{
		fmt.Println(a+2)
	}
}