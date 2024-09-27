package main

import "fmt"

func main() {
	var a, b int
	fmt.Scanln(&a, &b)
	result, err := divide(a, b)
	if err != nil {
		fmt.Println("ошибка")
	} else {
		fmt.Println(result)
	}
}

func divide(a int, b int) (int, error) {
	if b == 0 {
		return 0, fmt.Errorf("деление на ноль")
	}
	result := a / b
	return result, nil
}
