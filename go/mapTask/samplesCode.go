package main

import (
	"fmt"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	var mu sync.Mutex
	m := make(map[int]int)

	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			mu.Lock()
			m[i] = i * 2
			mu.Unlock()
		}(i)
	}

	wg.Wait()
	fmt.Println(m)
}
