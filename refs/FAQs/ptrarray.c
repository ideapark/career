#include <stdio.h>
#include <stddef.h>

struct stuff {
	char name[16];
};

struct stuff array[] = {
	{"The"},
	{"quick"},
	{"brown"},
	{"fox"},
	{"jumped"},
	{"over"},
	{"the"},
	{"lazy"},
	{"dog."}
};

#define ARRLEN(arr) (sizeof(arr)/sizeof(arr[0]))

int main(void)
{
	int i;
	for (i = 0; i < ARRLEN(array); i++)
		printf("%s\n", array[i].name);

	return 0;
}
