package main

import "fmt"

func main() {
	var number [5]int = [5]int{1, 2, 3, 4, 5}
	for i := 0; i < len(number); i++ {
		fmt.Println(number[i])
	}
	// cinArray()
	binNumber(2)
}

// функция получает на вход длинну массива
// вместо массива с фиксированной длинной  будем использовать  слайс ,так как длинна у нас не известна и мы будет получать ее от пользователя
// заполняем слайс с заданной  длинной
// выводим слайс в терминал
func cinArray() {
	var lenght_arr int
	fmt.Scanln(&lenght_arr)
	number := make([]int, lenght_arr)

	for i := 0; i < lenght_arr; i++ {
		fmt.Scanln(&number[i])
	}

	for i := 0; i < len(number); i++ {
		fmt.Print(number[i], " ")
	}
}

// функция выводит адрес в памяти переменной инта
func binNumber(number int) {
	result := &number
	fmt.Println(result)
}

