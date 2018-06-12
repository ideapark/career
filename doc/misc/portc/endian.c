#include <stdio.h>

int main(int argc, char *argv[])
{
	long int str[2] = { 0x41424344, 0x0 }; /* ASCII "ABCD" */
	printf("%s\n", (char*)&str);
	return 0;
}

/// NOTE:
///
/// A little-endian (e.g., VAX) will print "DCBA"
/// whereas a big-endian (e.g., MC68000 microprocessors) will print "ABCD"
///
/// The example will only function correctly if sizeof(long int) is 32 bits.
