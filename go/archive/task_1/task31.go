package main

import (
	"fmt"
	"math"
)

func main() {
	var x, p, y int
	fmt.Scan(&x, &p, &y)

	n := math.Ceil(math.Log(float64(y)/float64(x)) / math.Log(1+float64(p)/100))

	fmt.Println(int(n)) //Вклад в банке составляет x рублей

}
