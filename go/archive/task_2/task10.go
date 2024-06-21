package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)

	if n >= 0 && n < 100 {
		lastDigit := n % 10
		lastTwoDigits := n % 100

		switch {
		case lastDigit == 1 && lastTwoDigits != 11:
			fmt.Println(n, "korova")
		case lastDigit >= 2 && lastDigit <= 4 && (lastTwoDigits < 12 || lastTwoDigits > 14):
			fmt.Println(n, "korovy")
		default:
			fmt.Println(n, "korov")
		}
	}
}
