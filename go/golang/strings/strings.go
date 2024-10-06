package main

import (
	"fmt"
)

func ExampleByteSlice() {
	bs := []byte("This is byte slice")
	fmt.Printf("Так байтовый срез выглядит изнутри: %v\n", bs, "\n")

	for i := range bs {
		if bs[i]%2 == 0 {
			bs[i] = bs[i] + 1
			continue
		}
	}
	fmt.Printf("Изменяемый байтовый срез в виде строки: %s", bs, "\n")
}
func ExampleRune() {
	rs := []rune("Это срез рун")
	for i := range rs {
		if rs[i] == 'р' {
			rs[i] = '*'
		}
	}
	fmt.Printf("Измененный срез в виде строки: %s\n", string(rs), "\n")
}
func main() {
	ExampleByteSlice()
	fmt.Println("=========================")
	ExampleRune()
}
