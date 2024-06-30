package main

func main() {
	print(TwiceAsOld(36, 7))
}
func TwiceAsOld(dadYearsOld, sonYearsOld int) int {
	c := dadYearsOld - (sonYearsOld * 2)
	return c
}
