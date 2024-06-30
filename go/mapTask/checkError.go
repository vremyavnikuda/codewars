package main

import (
	"fmt"
)

func main() {
	var friendsOfDima []string
	friendsOfSemyon := make([]string, 3)
	friendsOfDima = append(friendsOfDima, "Костя", "Семён", "Таня")
	friendsOfSemyon = append(friendsOfSemyon, "Валера", "Таня", "Дима")
	friends := map[string][]string{
		"Dima":   friendsOfDima,
		"Semyon": friendsOfSemyon,
		"Костя":  nil,
	}

	_, value := friends["Костя"]
	fmt.Print(value, " ")
	delete(friends, "Dima")
	fmt.Print(friendsOfSemyon[3])
}
