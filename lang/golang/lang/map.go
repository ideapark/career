package main

func main() {
	type user struct {
		name string
		age  byte
	}

	m1 := map[int]user{
		1: {"Tom", 19},
	}

	// NOTE: hash algorithm and memory safe
	//       map's value is not addressable
	//m1[1].age += 1

	// reset whole value
	u := m1[1]
	u.age += 1
	m1[1] = u

	m2 := map[int]*user{
		1: &user{"Tom", 19},
	}

	// use pointer to change value's field
	m2[1].age += 1
}
