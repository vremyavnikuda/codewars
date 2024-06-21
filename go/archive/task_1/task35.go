package main

import "fmt"

func main() {
	swap()
}
func swap() {
	var workArray [10]uint8
	// Читаем 10 чисел и записываем их в массив
	for i := 0; i < 10; i++ {
		fmt.Scan(&workArray[i])
	}

	// Читаем 3 пары индексов для обмена элементов
	for i := 0; i < 3; i++ {
		var a, b int
		fmt.Scan(&a, &b)
		workArray[a], workArray[b] = workArray[b], workArray[a]
	}

	// Выводим элементы массива через пробел
	for _, v := range workArray {
		fmt.Print(v, " ")
	}
	fmt.Println("type ok")
	return
}
