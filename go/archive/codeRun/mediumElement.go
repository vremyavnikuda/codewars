package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	input = strings.TrimSpace(input)
	numStrings := strings.Split(input, " ")

	numbers := make([]int, 3)
	for i, numStr := range numStrings {
		num, _ := strconv.Atoi(numStr)
		numbers[i] = num
	}

	sort.Ints(numbers)
	fmt.Println(numbers[1])
}
