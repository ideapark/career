/*
CREATE TABLE `userinfo` (
	`uid`        INT(10) NOT NULL AUTO_INCREMENT,
	`username`   VARCHAR(64) NULL DEFAULT NULL,
	`departname` VARCHAR(64) NULL DEFAULT NULL,
	`created`    DATE NULL DEFAULT NULL,
	PRIMARY KEY (`uid`)
)
*/
package main

import (
	"database/sql"
	"fmt"
	"time"

	_ "github.com/bmizerany/pq"
)

const (
	DBUser     = "postgres"
	DBPassword = "postgres"
	DBName     = "test"
)

func main() {
	dbinfo := fmt.Sprintf("user=%s password=%s dbname=%s sslmode=disable", DBUser, DBPassword, DBName)
	db, err := sql.Open("postgres", dbinfo)
	checkErr(err)
	defer db.Close()

	fmt.Println("# Inserting values")
	var lastInsertId int
	err = db.QueryRow("INSERT INTO userinfo(username,departname,created) VALUES($1,$2,$3) RETURNING uid", "golang", "RND", "2012-12-09").Scan(&lastInsertId)
	checkErr(err)

	fmt.Println("# Updating")
	stmt, err := db.Prepare("UPDATE userinfo SET username=$1 WHERE uid=$2")
	checkErr(err)

	res, err := stmt.Exec("gopher", lastInsertId)
	checkErr(err)

	affect, err := res.RowsAffected()
	checkErr(err)

	fmt.Println(affect, "rows changed")

	fmt.Println("# Querying")
	rows, err := db.Query("SELECT * FROM userinfo")
	checkErr(err)

	for rows.Next() {
		var uid int
		var username string
		var department string
		var created time.Time
		err = rows.Scan(&uid, &username, &department, &created)
		checkErr(err)
		fmt.Println("uid | username | department | created ")
		fmt.Printf("%3v | %8v | %6v | %6v\n", uid, username, department, created)
	}

	fmt.Println("# Deleting")
	stmt, err = db.Prepare("DELETE FROM userinfo WHERE uid=$1")
	checkErr(err)

	res, err = stmt.Exec(lastInsertId)
	checkErr(err)

	affect, err = res.RowsAffected()
	checkErr(err)

	fmt.Println(affect, "rows changed")
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}
