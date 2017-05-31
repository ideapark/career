/*
CREATE TABLE `userinfo` (
	`uid`        INTEGER PRIMARY KEY AUTOINCREMENT,
	`username`   VARCHAR(64) NULL,
	`departname` VARCHAR(64) NULL,
	`created`    DATE NULL
)
*/
package main

import (
	"database/sql"
	"fmt"
	"time"

	_ "github.com/mattn/go-sqlite3"
)

func main() {
	db, err := sql.Open("sqlite3", "./gopher.db")
	checkErr(err)
	defer db.Close()

	// insert
	stmt, err := db.Prepare("INSERT INTO userinfo(username, departname, created) VALUES(?,?,?)")
	checkErr(err)

	res, err := stmt.Exec("gopher", "RND", "2012-12-09")
	checkErr(err)

	id, err := res.LastInsertId()
	checkErr(err)

	fmt.Println(id)

	// update
	stmt, err = db.Prepare("UPDATE userinfo SET username=? WHERE uid=?")
	checkErr(err)

	res, err = stmt.Exec("golang", id)
	checkErr(err)

	affect, err := res.RowsAffected()
	checkErr(err)

	fmt.Println(affect)

	// query
	rows, err := db.Query("SELECT * FROM userinfo")
	checkErr(err)
	defer rows.Close()

	var uid int
	var username string
	var department string
	var created time.Time

	for rows.Next() {
		err = rows.Scan(&uid, &username, &department, &created)
		checkErr(err)
		fmt.Println(uid)
		fmt.Println(username)
		fmt.Println(department)
		fmt.Println(created)
	}

	// delete
	stmt, err = db.Prepare("DELETE FROM userinfo WHERE uid=?")
	checkErr(err)

	res, err = stmt.Exec(id)
	checkErr(err)

	affect, err = res.RowsAffected()
	checkErr(err)

	fmt.Println(affect)
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}
