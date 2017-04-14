package semaphore

type Empty interface {}
type semaphore chan Empty

// acquire n resources
func (s semaphore) P(n int) {
	e := new(Empty)
	for i := 0; i < n; i++ {
		s <- e
	}
}

// release n resources
func (s semaphore) V(n int) {
	for i := 0; i < n; i++ {
		<-s
	}
}

/* mutexes */
func (s semaphore) Lock() {
	s.P(1)
}

func (s semaphore) Unlock() {
	s.V(1)
}

/* signal-wait */
func (s semaphore) Wait(n int) {
	s.P(n)
}

func (s semaphore) Signal() {
	s.V(1)
}
