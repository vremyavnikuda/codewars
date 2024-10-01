package main

import (
	"math"
)
func MxDifLg(a1 []string, a2 []string) int {
	if len(a1) == 0 || len(a2) == 0 {
		return -1
	}

	minA1, maxA1 := math.MaxInt32, 0
	for _, s := range a1 {
		length := len(s)
		minA1 = int(math.Min(float64(minA1), float64(length)))
		maxA1 = int(math.Max(float64(maxA1), float64(length)))
	}

	minA2, maxA2 := math.MaxInt32, 0
	for _, s := range a2 {
		length := len(s)
		minA2 = int(math.Min(float64(minA2), float64(length)))
		maxA2 = int(math.Max(float64(maxA2), float64(length)))
	}

	return int(math.Max(
		math.Abs(float64(maxA1-minA2)),
		math.Abs(float64(maxA2-minA1)),
	))
}
