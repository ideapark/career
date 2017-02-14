#include <time.h>
#include <stdio.h>
#include <stdarg.h>

void write_log(const char *function_name, unsigned int line_num,
		const char *format, ...)
{
	FILE *fp_log;
	if ((fp_log = fopen("./vaprintfs.log", "a+")) == NULL) {
		fprintf(stderr, "Can't open log file to write.\n");
		return;
	}

	time_t timestamp = time(NULL);
	va_list argptr;
	va_start(argptr, format);

	fprintf(fp_log, "%.8s %s (line %u): ", ctime(&timestamp)+11,
			function_name, line_num);
	vfprintf(fp_log, format, argptr);

	va_end(argptr);

	fclose(fp_log);
	fp_log = NULL;
}

int main(int argc, char *argv[])
{
	write_log(__func__, __LINE__, "argc = %d\n", argc);
	return 0;
}
