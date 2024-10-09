package main

import (
	"errors"
	"fmt"
)

func main() {
	var num1, num2 int
	fmt.Scan(&num1, &num2)
	result, err := divine(num1, num2)
	if err != nil {
		fmt.Println("ошибка")
	} else {
		fmt.Println(result)
	}
}
func divine(num1 int, num2 int) (int, error) {
	if num2 == 0 {
		return 0, errors.New("error")
	}
	return num1 / num2, nil
}
