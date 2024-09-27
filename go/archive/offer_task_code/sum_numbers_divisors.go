package main

//Посчитайте колко делителей натурального числа
func Divisors(n int) int {

	//счетчик делителей натурального числа
	sum := 0
	if n == 0 {
		return 0
	}
	for i := 1; i <= n; i++ {
		if n%i == 0 {
			sum++
		}
	}
	return sum
}
