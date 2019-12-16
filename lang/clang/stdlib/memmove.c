#include <string.h>
#include <stdio.h>

int main(void)
{
	char a[30] = "That's not what I said.";

	puts(a);
	memmove(a + 7, a + 11, 13);	/* move 13 bytes, 'w' to '\0' */
	puts(a);

	return 0;
}
