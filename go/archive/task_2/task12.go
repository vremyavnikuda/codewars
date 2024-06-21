package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	arrayFibo := fibo(n)
	fmt.Println(fiboNumber(arrayFibo, n))
}

func fiboNumber(arrayFibo []int, n int) int {
	for i := 0; i < len(arrayFibo); i++ {
		if arrayFibo[i] == n {
			return i
		}
	}
	return -1
}

func fibo(n int) []int {
	var arrayFibo []int

	if n >= 1 {
		arrayFibo = append(arrayFibo, 0)
	}

	if n >= 2 {
		arrayFibo = append(arrayFibo, 1)
	}

	for i := 2; i < n; i++ {
		nextFibo := arrayFibo[i-1] + arrayFibo[i-2]
		arrayFibo = append(arrayFibo, nextFibo)
	}

	return arrayFibo
}

/*
package main

import "fmt"

func main() {
	var A int
	fmt.Scan(&A)
	fmt.Println(fiboNumber(A))
}

func fiboNumber(A int) int {
	if A == 0 {
		return 0 // Первое число Фибоначчи
	}

	a, b := 0, 1 // Первые два числа Фибоначчи
	order := 1   // Порядковый номер текущего числа Фибоначчи

	for b <= A {
		if b == A {
			return order // Если нашли число Фибоначчи, возвращаем его порядковый номер
		}
		a, b = b, a+b // Переход к следующему числу Фибоначчи
		order++       // Увеличение порядкового номера
	}

	return -1 // Если не нашли число Фибоначчи, возвращаем -1
}
*/
