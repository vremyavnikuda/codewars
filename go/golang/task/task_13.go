package main

import (
	"fmt"
	"strconv"
)

func main() {
	var number int
	fmt.Scan(&number)
	if number != 0 {
		fmt.Println(strconv.FormatInt(int64(number), 2))
	}
}
