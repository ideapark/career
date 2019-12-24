package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"time"
)

type Website struct {
	Name string
	Year int
	URL  string
}

var websites = []Website{
	{Name: "Python", Year: 1991, URL: "http://python.org/"},
	{Name: "Ruby", Year: 1995, URL: "http://www.ruby-lang.org/en/"},
	{Name: "Scala", Year: 2003, URL: "http://www.scala-lang.org/"},
	{Name: "Go", Year: 2009, URL: "http://golang.org/"},
}

func forAll(sites []Website, f func(Website)) {
	for _, website := range sites {
		f(website)
	}
}

func countBytesInBody(r *http.Response) int64 {
	// copy the content to a black hole, counting the bytes copied
	n, _ := io.Copy(ioutil.Discard, r.Body)
	r.Body.Close()
	return n
}

func timeWebsiteResponse(name, url string, c chan<- string) {
	start := time.Now()
	r, err := http.Get(url)
	if err != nil {
		c <- fmt.Sprintf("%s: %s\n", name, err)
		return
	}
	n := countBytesInBody(r)
	c <- fmt.Sprintf("%s %d [%.2fs]\n", name, n, time.Since(start).Seconds())
}

func main() {
	start := time.Now()
	c := make(chan string)
	n := 0
	forAll(websites, func(website Website) {
		n++
		go timeWebsiteResponse(website.Name, website.URL, c)
	})

	timeout := time.After(2 * time.Second)
	for i := 0; i < n; i++ {
		select {
		case result := <-c:
			fmt.Printf(result)
		case <-timeout:
			fmt.Println("Timed out.")
			return // no more response will be in time
		}
	}

	fmt.Printf("%.2fs total\n", time.Since(start).Seconds())
}
