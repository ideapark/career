package main

import (
	"fmt"
	"log"
	"log/syslog"
)

func main() {
	syslog, err := syslog.Dial("tcp", "localhost:1234", syslog.LOG_WARNING|syslog.LOG_DAEMON, "demotag")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Fprintf(syslog, "This is a daemon warning with demotag.")
	syslog.Emerg("And this is a daemon emergency with demotag.")
}
