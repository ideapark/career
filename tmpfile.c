/*
 * demonstrate tmpfile().
 */
#include <stdio.h>

int main(void)
{
    static char mesg[] = "Here's lookin at you, kid!";
    FILE *fp;
    char buf[BUFSIZ];

    fp = tmpfile();
    fprintf(fp, "%s", mesg);
    fflush(fp);

    rewind(fp);
    fgets(buf, sizeof(buf), fp);

    printf("Get back <%s>\n", buf);

    fclose(fp);
    return 0;
}
