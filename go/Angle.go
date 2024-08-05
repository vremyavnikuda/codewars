package main

func main() {
	println(Angle(6))
}

func Angle(n int) int {
	if n < 2 {
		return 0
	}
	return (n - 2) * 180
}
