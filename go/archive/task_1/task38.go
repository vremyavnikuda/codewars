package main

import "fmt"

// The main function in Go takes user input to create an array of integers and then prints out the
// elements at even indices.
func main() {
	//Задаем длину массива
	var lengthArray int
	//Получаем от пользователя длину массива
	fmt.Scan(&lengthArray)
	//Вызываем функцию для заполнения массива
	array := make([]int, lengthArray)
	//Заполняем массив
	for i:=0;i<lengthArray;i++{
		fmt.Scan(&array[i])
	}
	//Перебираем массив по четным индексам
	for i :=0 ; i <lengthArray; i+=2{
		fmt.Print(array[i]," ")
	}
	fmt.Println()
}