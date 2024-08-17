package main

import "fmt"

func main() {
	x := func(fn func(i int) int, i int) func(int) int { return fn }(func(i int) int { return i + 1 }, 5)
	fmt.Printf("%T\n", x)

	fmt.Println(Add(2, 3))

	age := 18
	name := "Andrew"
	Update(&age, &name)
	fmt.Println(age, name)
	fmt.Println(area(2, 3))
	fmt.Println(summa)
}

//функция с двумя переменными и возвращаемым одним значением
func Add(x int, y int) (result int) {
	result = x + y
	return result
}

//функция с двумя переменными
func Update(a *int, b *string) {
	*a = *a + 1
	*b = *b + "hello"
	return
}

//анонимная функция
var(area=func(l int,b int)int{
	return l*b
})

//анонимная функция и сразу же передаем значения переменных вместо значений переменных можно передать сами переменные 
var (
	summa=func(l int,b int)int{
		return l+b
	}(20,30)
)