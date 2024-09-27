package main

type test struct {
	On    bool
	Ammo  int
	Power int
}

func (t *test) Shoot() bool {
	if t.On == false {
		return false
	} else if t.Ammo > 0 {
		t.Ammo--
		return true
	} else {
		return false
	}
}

func (t *test) RideBike() bool {
	if t.On == false {
		return false
	} else if t.Power > 0 {
		t.Power--
		return true
	} else {
		return false
	}
}

func main() {
	testStruct := new(test)
	println(testStruct)
}
