#include <string.h>

int main(void)
{
	char *weekdays[] = {
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};
	char date[] = "Thu, 10 Mar 2005 13:44:18 +0100";
	int dow;
	for (dow = 0; dow < 7; dow++)
		if (strncmp(date, weekdays[dow], 3) == 0)
			break;

	return 0;
}
