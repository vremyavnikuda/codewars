package main

import "fmt"

func main(){
	a,b:=sumInt(1,0)
	fmt.Println(a,b)

}

func sumInt(a...int)(count int,resultSum int){
	var resultCount ,resultElem int
	for _,elem := range a{
		resultElem+=elem
		resultCount++
	}
	fmt.Println(resultCount,resultElem)
	return resultCount,resultElem
}