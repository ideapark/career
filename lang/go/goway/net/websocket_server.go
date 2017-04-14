package main

import (
	"fmt"
	"net/http"
	"websocket"
)

func server(ws *websocket.Conn) {
	fmt.Printf("new connection\n")
	buf := make([]byte, 100)
	for {
		if _, err := ws.Read(buf); err != nil {
			fmt.Printf("%s", err, Error())
			break;
		}
	}
	fmt.Printf(" => closing connection\n")
	ws.Close()
}

func main() {
	http.Handle("/websocket", websocket.Handler(server))
	err := http.ListenAndServer(":12345", nil)
	if err != nil {
		panic("ListenAndServer: " + err.Error())
	}
}
