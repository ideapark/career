#include <string.h>
#include <stdio.h>

int main(void)
{
	FILE *fpTx;
	FILE *fpRx;
	FILE *fpLog;
	char rxbuffer[2048];
	char *found;

	if ((fpRx = fopen("./strstr.c", "r+")) == NULL) {
		fprintf(stderr, "Can't open file \"./strstr.c\" to read.\n");
		return -1;
	}

	if ((fpLog = fopen("./strstr.log", "w+")) == NULL) {
		fprintf(stderr, "Can't open log file \"./strstr.log\" to write.\n");
		fclose(fpRx), fpRx = NULL;
		return -2;
	}

	if ((fpTx = fopen("./strstr.tx", "w+")) == NULL) {
		fprintf(stderr, "Can't open tx file \"./strstr.tx\" to write.\n");
		fclose(fpRx), fpRx = NULL;
		fclose(fpLog), fpLog = NULL;
		return -3;
	}

	fgets(rxbuffer, 2048, fpRx);
	found = strstr(rxbuffer, "assword:");
	if (found != NULL) {
		fputs("Got password prompt. Sending password", fpLog);
		fputs("topsecret", fpTx);
	}

	fclose(fpRx), fpRx = NULL;
	fclose(fpTx), fpTx = NULL;
	fclose(fpLog), fpLog = NULL;

	return 0;
}
