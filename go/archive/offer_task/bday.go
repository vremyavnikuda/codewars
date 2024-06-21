package main

import (
	"fmt"
	"time"
)

func dDay() {
	bday := "1990-07-02T17:00:00.000Z"

	currentDataNow := time.Now()
	bdayParse, err := time.Parse(time.RFC3339, bday)
	if err != nil {
		panic("Ошибка парсинга даты рождения")
	}

	formatedData := bdayParse.Format("2006-01-02")

	// Получаем год напрямую из объекта времени, не требуется преобразование строки в число
	age := currentDataNow.Year() - bdayParse.Year()
	if currentDataNow.YearDay() < bdayParse.YearDay() {
		age--
	}

	fmt.Println(formatedData)
	fmt.Println(age)
}
