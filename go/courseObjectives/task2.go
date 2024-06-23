package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {

	addSymbol()
}

func addSymbol() {
	// Создаем reader для считывания входных данных
	reader := bufio.NewReader(os.Stdin)
	// Считываем строку
	input, _ := reader.ReadString('\n')
	// Убираем символ новой строки
	input = strings.TrimSpace(input)

	// Создаем builder для формирования результата
	var builder strings.Builder

	// Проходим по каждому символу строки
	for i, char := range input {
		if i > 0 {
			builder.WriteString("*")
		}
		builder.WriteRune(char)
	}

	// Печатаем результат
	fmt.Println(builder.String())
}
