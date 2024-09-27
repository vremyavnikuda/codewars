package main

import (
	"errors"
	"fmt"
)

func main() {
	for i := 0; i < 10; i++ {
		i := i + 1
		fmt.Println(i)
	}

	loopRange(2)
	Func1()
}

var (
	loopRange = func(number int) int {
		for i := 0; i <= number; i++ {
			i := i + 1
			return i
		}
		func(number int) {
			for numbers := range number {
				if number%2 == 0 {
					continue
				}
				fmt.Println(numbers)
			}
		}(20)
		return 0
	}
)

type DivisionError struct {
	IntA int
	IntB int
	Msg  string
}

func (e *DivisionError) Error() string {
	return e.Msg
}
func Devine(a, b int) (float64, error) {
	if b == 0 {
		return 0, &DivisionError{
			Msg:  "devide by zero",
			IntA: a, IntB: b,
		}
	}
	return float64(a / b), nil
}

func Func1() float64 {
	a, b := 3, 2
	result, err := Devine(a, b)
	if err != nil {
		var divErr *DivisionError
		switch {
		case errors.As(err, &divErr):
			fmt.Printf("%d / %d is not mathematically valid: %s\n",
				divErr.IntA, divErr.IntB, divErr.Error())
		default:
			fmt.Println(result)
		}
	}
	fmt.Printf("%d / %d = %d\n", a, b, result)
	return result
}
