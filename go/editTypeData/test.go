package main

import "strconv"

func main() {
	res := []rune("text")
	println(res)
	re := string([]byte("text"))
	println(re)
	a := 10.123
	res1 := int64(a)
	println(res1)
	res2 := 101.0 / 10
	println(res2)
	res3 := strconv.Itoa(int(float64(100/10)) + 1)
	println(res3)
	res4 := strconv.FormatBool(10 == int16(float64((100 / 10))))
	println(res4)
	/*res5 := (strconv.FormatBool(true)) == (10 == int(float64(100/10)))
	println(res5)*/
	res6 := strconv.FormatBool(10.1 == float32(float64(100/10.1)))
	println(res6)
}
