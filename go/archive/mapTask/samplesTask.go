package main

func main() {
	m := make(map[string]int)
	for _, word := range []string{
		"hello",
		"world",
		"from",
		"the",
		"best",
		"language",
		"in",
		"the",
		"world",
	} {
		m[word]++
	}
	for k, v := range m {
		println(k, v)
	}
}
