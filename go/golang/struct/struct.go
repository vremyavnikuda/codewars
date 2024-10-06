package main

import (
	"fmt"
	"math"
)

type Circle struct {
	x, y, r float64
}
type Rectangle struct {
	x1, x2, y1, y2 float64
}
type Person struct {
	Name string
}
type Android struct {
	Person
	Model string
}

func distance(d *Rectangle) float64 {
	a := d.x2 - d.x1
	b := d.y2 - d.y1
	return math.Sqrt(a*a + b*b)
}
func (d *Rectangle) area() float64 {
	l := distance(d)
	w := distance(d)
	return l * w
}
func (c *Circle) area() float64 {
	return math.Pi * c.r * c.r
}

func (p *Person) talk() {
	fmt.Println("Hi ,my name is " + p.Name)
}

func main() {
	r := &Rectangle{x1: 12, x2: 10, y1: 5, y2: 5}
	fmt.Println(r.area())
	c := &Circle{1, 1, 2}
	fmt.Println(c.area())
	a := new(Android)
	a.talk()
}
