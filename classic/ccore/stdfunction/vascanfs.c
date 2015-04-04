#include <stdio.h>
#include <stdarg.h>

typedef struct {
    char lastname[20];
    char firstname[20];
    int  dob_month;
    int  dob_day;
    int  dob_year;
} person;

int read_person(char *lname, char *fname, ...)
{
    va_list args;
    int count;

    printf("Enter the last name and first name (eg: Smith, Sally)\n");
    count = scanf("%[^,], %[^\n]", lname, fname); /* read from stdin */

    va_start(args, fname);
    if (count == 2 && va_arg(args, int*) != NULL) {
        va_end(args);
        va_start(args, fname); /* re-init */

        printf("Enter the date of birth, (eg: 9/21/1962)\n");
        count += vscanf("%d/%d/%d", args); /* read birthday */
    }

#ifdef DEBUG
    fprintf(stderr, "Read %d fields.\n", count);
#endif // def DEBUG

    va_end(args);
    return count;
}

int main(void)
{
    person employee;
    person *pe = &employee;
    int result;

    result = read_person(
            pe->lastname,
            pe->firstname,
            pe->dob_month,
            pe->dob_day,
            pe->dob_year);
#ifdef DEBUG
    fprintf(stderr, "Fields read: %s, %s; born %d-%d-%d\n",
            pe->lastname,
            pe->firstname,
            pe->dob_month,
            pe->dob_day,
            pe->dob_year);
#endif // def DEBUG
    return result > 0;
}
