package main

import (
	"fmt"
	"time"
)

func work(x int) int {
	if x > 3 {
		time.Sleep(time.Millisecond * 500)
		return x + 1
	} else {
		time.Sleep(time.Millisecond * 500)
		return x - 1
	}
}

func main() {
	var n int
	cache := make(map[int]int)

	for i := 0; i < 10; i++ {
		fmt.Scan(&n)
		if _, ok := cache[n]; !ok {
			cache[n] = work(n)
		}
		fmt.Print(cache[n], " ")
	}
}