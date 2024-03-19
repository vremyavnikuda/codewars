package main

import "fmt"

func PrinterError(s string) string {
	errorCount := 0

	total := len(s)

	for _, char := range s {
		if char < 'a' || char > 'm' {
			errorCount++
		}
	}
	return fmt.Sprintf("%d/%d", errorCount, total)
}
