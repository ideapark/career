/*
Server is a very simple static file server written in golang

Usage:
    -p="9090" port to listen
    -d="."    the directory of static file to host
*/
package main

import (
	"flag"
	"log"
	"net/http"
)

func main() {
	port := flag.String("port", "9090", "server port")
	dir := flag.String("dir", ".", "directory of static file to host")
	flag.Parse()

	http.Handle("/", http.FileServer(http.Dir(*dir)))
	log.Fatal(http.ListenAndServe(":"+*port, nil))
}
