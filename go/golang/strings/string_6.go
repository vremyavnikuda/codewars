package main

import "fmt"

func main() {
	var a string
	fmt.Scanln(&a)
	fmt.Println(confPassord(a))
}

func confPassord(pass string) string {
	rs := []rune(pass)
	if len(pass) == len(rs) && len(rs) >= 5 {
		z := true
		for _, elem := range rs {
			if !isLetterOrDigit(elem) {
				z = false
				break
			}
		}
		if z {
			return "Ok"
		} else {
			return "Wrong password"
		}
	} else {
		return "Wrong password"
	}
}
func isLetterOrDigit(r rune) bool {
	return (r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z') || (r >= '0' && r <= '9')
}
