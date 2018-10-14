#include <stdio.h>
#include <errno.h>

int main(void)
{
	char fname_tmp[L_tmpnam] = "";
	FILE *fp;
	int result;

	tmpnam(fname_tmp);
	fp = fopen(fname_tmp, "w+");

	/* ... write something to file ... */

	fclose(fp);
	result = rename(fname_tmp, "remove.ts");
	if (result) {
		remove("remove.ts");
		result = rename(fname_tmp, "remove.ts");
		if (result)	/* rename() error */
			fprintf(stderr,
				"Error %d on trying to rename output file\n",
				errno);
	}
	return 0;
}
