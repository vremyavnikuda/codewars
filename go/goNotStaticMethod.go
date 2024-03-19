package main

import "fmt"

type GoNotStaticMethod struct {
	value int
}

func (t GoNotStaticMethod) GoNotStaticMethod() int {
	return t.value * 2
}

func main() {
	t := GoNotStaticMethod{
		value: 10,
	}
	result := t.GoNotStaticMethod()
	fmt.Println(result)
}
