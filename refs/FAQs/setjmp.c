#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf saved_state;

void call_longjmp(void)
{
	longjmp(saved_state, 1);
}

int main(void)
{
	int ret_code;

	printf("The current state of the program is being saved...\n");
	ret_code = setjmp(saved_state);
	if (ret_code == 1) {
		printf("The longjmp function has been called.\n");
		printf("The program's previous state has been restored.\n");
		exit(0);
	}
	printf("I am about to call longjmp and\n");
	printf("return to the previous program state...\n");
	call_longjmp();
	return 0;
}
