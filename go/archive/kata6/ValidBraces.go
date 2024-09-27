package main

func ValidBraces(str string) bool {
	stack := []rune{}

	matchingBraces := map[rune]rune{
		')': '(',
		'}': '{',
		']': '[',
	}
	for _, char := range str {
		switch char {
		case '(', '{', '[':
			stack = append(stack, char)
		case ')', '}', ']':
			if len(stack) == 0 || stack[len(stack)-1] != matchingBraces[char] {
				return false
			}
			stack = stack[:len(stack)-1]
		}
	}
	return len(stack) == 0
}

func main() {
	println(ValidBraces("(){}[]"))
}
