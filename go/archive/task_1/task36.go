package main

import "fmt"

func sliceIndex(array []int) {
	// Заполняем массив
	for i := 0; i < len(array); i++ {
		fmt.Scan(&array[i])
	}
	// Выводим элемент по индексу
	fmt.Println(array[4-1])
}

func main() {
	// Читаем длину массива
	var length int
	// Получаем от пользователя длину массива
	fmt.Scan(&length)

	// Вызываем функцию для заполнения массива
	sliceIndex(make([]int, length))
}
