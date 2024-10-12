package main

import "fmt"

func main() {
	var mp map[string]int = map[string]int{
		"apple":  5,
		"pear":   6,
		"orange": 3,
	}
	fmt.Println(mp["apple"])
	mp["apple"] = 900
	fmt.Println(mp)

	mpNew := make(map[string]int)

	fmt.Println(mpNew)
	val, ok := mp["orange"]
	fmt.Println(val, ok)
	fmt.Println(len(mp))
	for key,value:=range mp{
		fmt.Println(key,":",value)
	}
}
