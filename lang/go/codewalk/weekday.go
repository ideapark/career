package main

import (
	"fmt"
)

// A Weekday specifies a day of the week
type Weekday int

// For all seven days of the week, declare a constant of type Weekday
// (Sunday=0, ...).
const (
	Sunday Weekday = iota
	Monday
	Tuesday
	Wednesday
	Thursday
	Friday
	Saturday
)

var days = []string{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
}

// String returns the English name of the day ("Sunday", "Monday", ...).
func (d Weekday) String() string {
	return days[d]
}

func main() {
	day := Weekday(4)
	fmt.Printf("Day %d is %s\n", day, day)
}
