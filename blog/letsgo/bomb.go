package main

import "time"

func main() {
	tick := time.Tick(500 * time.Millisecond)
	timer := time.NewTimer(5 * time.Second)

	for {
		select {
		case <-tick:
			println("tick...")
		case <-timer.C:
			println("bomb")
			return
		}
	}
}
