package main

func solution(str, ending string) bool {
	if len(str) >= len(ending) && str[len(str)-len(ending):] == ending {
		return true
	}
	return false
}
func main() {
	str := "abc"
	ending := "d"
	println(solution(str, ending))
}
