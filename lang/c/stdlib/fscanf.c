/* Example data:
 *  tony:x:1002:31:Tony Crawford,,,:/home/tony:/bin/bash
 */

#include <limits.h>		/* UINT_MAX */
#include <stdio.h>
#include <string.h>

struct pwrecord {
	unsigned int uid;
	unsigned int gid;
	char user[32];
	char pw[32];
	char realname[128];
	char home[128];
	char shell[128];
};

int main(void)
{
	FILE *fp;
	int results = 0;
	struct pwrecord record;
	struct pwrecord *recptr = &record;
	char gecos[256] = "";

	fp = fopen("./passwd", "r");
	if (fp == NULL) {
		perror("Read password file");
		return -1;
	}
	record = (struct pwrecord) {
	UINT_MAX, UINT_MAX, "", "", "", "", ""};
	results = fscanf(fp, "%32[^:]:%32[^:]:%u:%u", recptr->user, recptr->pw,
			 &recptr->uid, &recptr->gid);

	if (results < 4) {
		fprintf(stderr, "Unable to parse line.\n");
		fscanf(fp, "%*[^\n]\n");	/* read and discard remaining text */
	}

	results = fscanf(fp, "%256[^:]:", gecos);
	if (results < 1)
		strcpy(recptr->realname, "[No real name available]");
	else
		sscanf(gecos, "%128[^,]", recptr->realname);	/* trim at comma sign */

	results =
	    fscanf(fp, "%128[^:]:%128[^:\n]\n", recptr->home, recptr->shell);
	if (results < 2) {
		fprintf(stderr, "Unable to parse line.\n");
		fscanf(fp, "%*[^\n]\n");	/* read and discard reamaining text */
	}
	printf("The user account %s with UID %u belongs to %s.\n",
	       recptr->user, recptr->uid, recptr->realname);

	return 0;
}
