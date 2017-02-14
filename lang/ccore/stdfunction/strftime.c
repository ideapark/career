#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t now;
	struct tm *localnow;
	char hdr_date[999] = "";

	time(&now);
	localnow = localtime(&now);

	if (strftime(hdr_date, 78, "Date: %a, %d %b %Y %m %z", localnow)) {
		puts(hdr_date);
		return 0;
	} else {
		return -1;
	}
}
