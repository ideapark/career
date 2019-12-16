package main

import (
	"fmt"
	"hash/crc32"
)

func main() {
	// In this package, the CRC polynomial is represented in reversed notation,
	// or LSB-first representation.
	//
	// LSB-first representation is a hexadecimal number with n bits, in which the
	// most significant bit represents the coefficient of X^ and the least significant
	// bit represents the coefficient of X^n-1 (the coefficient for X^n is implicit).
	//
	// For example, CRC32-Q, as defined by the following polynomial,
	//      X^32 + X^31 + X^24 + X^22 + X^16 + X^14 + X^8 + X^7 + X^5 + X^3 + X^1 + X^0
	// has the reversed notation 0b11010101100000101000001010000001, so the value
	// that should be passed to MakeTable is 0xD5828281.
	crc32q := crc32.MakeTable(0xD5828281)
	fmt.Printf("%08x\n", crc32.Checksum([]byte("Hello world"), crc32q))
}
