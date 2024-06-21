package main

import "fmt"

func main() {
	var nSize int
	fmt.Scan(&nSize)
	//Создаем массив
	arrayNum := make([]int, nSize)
	if len(arrayNum) == 0 {
		panic("Пустой массив")
	}
	//Заполняем массив данными
	for i := 0; i < len(arrayNum); i++ {
		fmt.Scan(&arrayNum[i])
	}
	
	//Подсчет минимального числа
	min := arrayNum[0]
	for _, val := range arrayNum {
		if val < min {
			min = val
		}
	}
	count := 0
	for _, val := range arrayNum {
		if val == min {
			count++
		}
	}

	fmt.Println(count)
}
