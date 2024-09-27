package main

import "fmt"

// GoNotStaticMethod пример реализации статического метода в golang ->
// так как базовой реализации не поддерживает статические методы
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
