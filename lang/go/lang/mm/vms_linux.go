package main

import (
	"fmt"
	"os"

	"github.com/shirou/gopsutil/process"
)

func mem() {
	p, err := process.NewProcess(int32(os.Getpid()))
	if err != nil {
		panic(err)
	}
	m, err := p.MemoryInfoEx()
	if err != nil {
		panic(err)
	}
	fmt.Printf("VMS:%dMb, RSS:%dMb\n", m.VMS>>20, m.RSS>>20)
}

func main() {
	mem()

	// 10*1Mb
	data := new([10][1024 * 1024]byte)

	// only reserve address space
	mem()

	for i := range data {
		for x, n := 0, len(data[i]); x < n; x++ {
			data[i][x] = 1
		}
		// actually memory used
		mem()
	}
}
