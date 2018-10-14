#include <string.h>
#include <stdio.h>

int main(void)
{
	char *mnemonic;
	char *arg1;
	char *arg2;
	char *comment;
	char line[] = " mul eax,[ebp+4] ;\nMultiply by y\n";

	mnemonic = strtok(line, " \t");
	arg1 = strtok(NULL, ",");
	arg2 = strtok(NULL, ";\n");
	comment = strtok(NULL, "\n\r\v\f");
	printf("Command:      %s\n"
	       "1st argument: %s\n"
	       "2nd argument: %s\n"
	       "Comment:      %s\n\n", mnemonic, arg1, arg2, comment);

	return 0;
}
