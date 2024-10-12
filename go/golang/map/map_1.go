package main

import "fmt"

func main() {
	groupCity := map[int][]string{
		10:   []string{"Деревня", "Село"},
		100:  []string{"Город", "Большой город"},
		500:  []string{"Новосибирск", "Санк - Питербург"},
		1000: []string{"Миллионик"},
	}
	cityPopulation := map[string]int{
		"Деревня":         50,
		"Село":            70,
		"Город":           150,
		"Большой город":   500,
		"Миллионик":       1200,
		"Небольшой город": 80,
	}

	validCities := make(map[string]bool)
	for key, value := range groupCity {
		if key >= 100 && key < 1000 {
			for _, city := range value {
				validCities[city] = true
			}
		}
	}

	// Удаляем города из cityPopulation, которые не входят в validCities
	for city := range cityPopulation {
		if !validCities[city] {
			delete(cityPopulation, city)
		}
	}

	for city := range validCities {
		fmt.Println(city)
	}
}
