package main

import (
	"fmt"
	"net/http"
	"os"
	"sync/atomic"
)

// Simple count server.
type Counter struct {
	c int64
}

func (ctr *Counter) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	atomic.AddInt64(&ctr.c, 1)
	fmt.Fprintf(w, "counter = %d\n", ctr.c)
}

// A channel what sends a notification on each visit.
// (Probably want the channel to be buffered.)
type Chan chan *http.Request

func (ch Chan) ServeHTTP(w http.ResponseWriter, req *http.Request) {
	ch <- req
	fmt.Fprint(w, "notification sent")
}

// Argument server.
func ArgServer(w http.ResponseWriter, req *http.Request) {
	fmt.Fprintln(w, os.Args)
}

func main() {
	ctr := new(Counter)
	http.Handle("/counter", ctr)

	ch := make(Chan, 5)
	go func(ch Chan) {
		for {
			req := <-ch
			fmt.Println(req.Host, req.Method, req.UserAgent())
		}
	}(ch)
	http.Handle("/notify", ch)

	http.Handle("/args", http.HandlerFunc(ArgServer))
	http.ListenAndServe(":8080", nil)
}
