package login

func login() {
	if f1, err := os.Open("/etc/group"); err != nil {
		log.Fatalln(err)
	}
	defer f1.Close()

	if f2, err := os.Open("/etc/passwd"); err != nil {
		log.Fatalln(err)
	}
	defer f2.Close()

	if f3, err := os.Open("/etc/no-such-file"); err != nil {
		log.Fatalln(err)
	}
	// all resource ready, continue...
}
