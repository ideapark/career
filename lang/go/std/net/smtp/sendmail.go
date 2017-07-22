package main

import (
	"log"
	"net/smtp"
)

func main() {
	// Set up authentication information.
	auth := smtp.PlainAuth("", "p@ctriple.cn", "you cannt guess", "smtp.ctriple.cn")

	// Connect to the server, authenticate, set the sender and recipient,
	// and send the email all in one step.
	to := []string{"g@ctriple.cn"}
	msg := []byte("To: g@ctriple.cn\r\n" +
		"Subject: discount Gophers!\r\n" +
		"\r\n" +
		"This is the email body.\r\n")
	err := smtp.SendMail("smtp.ctriple.cn:25", auth, "p@ctriple.cn", to, msg)
	if err != nil {
		log.Fatal(err)
	}
}
