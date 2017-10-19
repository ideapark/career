package main

import (
	"encoding/json"
)

type user struct {
	Email    string `json:"email"`
	Password string `json:"password"`
}

var u = &user{
	Email:    "p@ctriple.cn",
	Password: "You got it!",
}

func main() {
	// 1. Omitting fields
	type publicUser1 struct {
		*user
		Password string `json:"password,omitempty"`
	}
	buf1, err1 := json.Marshal(publicUser1{user: u})
	if err1 == nil {
		println(string(buf1))
	}

	// 2. Adding extra fields
	type omit struct{}
	type publicUser2 struct {
		*user
		Password *omit `json:"password,omitempty"`
	}
	buf2, err2 := json.Marshal(publicUser2{user: u})
	if err2 == nil {
		println(string(buf2))
	}
}
