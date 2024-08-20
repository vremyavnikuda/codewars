package main

import (
	"fmt"
)

func stoneGameII(piles []int) int {
	n := len(piles)

	// Создаем таблицу dp, где dp[i][m] будет хранить максимальное количество камней,
	// которое может получить игрок, начиная с i-й кучи при M = m
	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, n+1)
	}

	// suffixSum[i] хранит сумму всех камней от i-й кучи до конца
	suffixSum := make([]int, n+1)
	for i := n - 1; i >= 0; i-- {
		suffixSum[i] = suffixSum[i+1] + piles[i]
	}

	// Заполняем таблицу dp снизу вверх
	for i := n - 1; i >= 0; i-- {
		for m := 1; m <= n; m++ {
			for x := 1; x <= 2*m && i+x <= n; x++ {
				dp[i][m] = maxWithoutFunction(dp[i][m], suffixSum[i]-dp[i+x][maxWithoutFunction(m, x)])
			}
		}
	}

	// Возвращаем результат для начального состояния (0, 1)
	return dp[0][1]
}

// Функция для сравнения двух значений
func maxWithoutFunction(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	fmt.Println(stoneGameII([]int{1, 2, 3, 4, 5, 100}))
}
