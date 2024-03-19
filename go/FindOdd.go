package main

//Найти нечетное значение int
func FindOdd(seq []int) int {
	//счетчик повторяющихся элементов
	counts := make(map[int]int)

	//проходимация по массиву
	for _, num := range seq {
		counts[num]++
	}

	//поиск нечетного значения
	for num, counts := range counts {
		if counts%2 != 0 {
			return num
		}
	}
	return 0
}
