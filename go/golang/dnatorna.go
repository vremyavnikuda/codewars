package main

import (
	"fmt"
	"strings"
)

func main() {
	fmt.Println(DNAtoRNA("GCAT"))
}

func DNAtoRNA(dna string) string {
	var result string
	if dna == "" {
		return ""
	} else {
		result = strings.ReplaceAll(dna, "T", "U")
	}
	return result
}
