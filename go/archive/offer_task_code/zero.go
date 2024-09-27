package main

func zero(x *int) {
	*x = 100
}
func main() {
	x := 5
	zero(&x)
	println(x)
}
