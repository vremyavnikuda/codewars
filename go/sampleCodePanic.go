package main

import (
	"errors"
	"fmt"
)

var global int64 = 1

type data struct {
	info    string
	counter int
	add     int32
}

func (data *data) save() (b uint64) {
	global--
	fmt.Println("saving...")
	return uint64(data.counter)
}

func main() {
	if err, data := create("", 0); err != nil {
		defer func() {
			data.save()
			fmt.Println("saved")
			fmt.Println("global", global)
		}()
		panic(err)
	}
}

func create(info string, count int) (error, data) {
	if len(info) == 0 {
		return errors.New("len if 0"), data{info: "", counter: 0, add: 0}
	}
	data := data{
		info:    info,
		counter: count,
		add:     1,
	}
	global++
	return nil, data
}
