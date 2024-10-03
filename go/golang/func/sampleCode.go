package main

import "fmt"

func main(){
	MyPrint(1,2,3,4,5)
}

func MyPrint(a...interface{}){
	for _,elem := range a{
		fmt.Printf("%d",elem)
	}
}