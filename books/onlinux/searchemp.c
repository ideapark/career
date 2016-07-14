#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct employee {
	char lastname[30];
	char firstname[30];
	long emp_id;
	time_t start_date;
};

/*
 * compare by ID
 */
int emp_id_compare(const void *e1p, const void *e2p)
{
	const struct employee *e1, *e2;

	e1 = (const struct employee *)e1p;
	e2 = (const struct employee *)e2p;

	if (e1->emp_id < e2->emp_id)
		return -1;
	else if (e1->emp_id == e2->emp_id)
		return 0;
	else
		return 1;
}

/*
 * print an employee structure
 */
void print_employee(const struct employee *emp)
{
	printf("%s %s\t%ld\t%s", emp->lastname, emp->firstname,
			emp->emp_id, ctime(&emp->start_date));
}

int main(int argc, char *argv[])
{
#define NPRES 10
	int i, npres;
	char buf[BUFSIZ];
	struct employee *the_pres;
	struct employee key;
	struct employee presidents[NPRES];
	int id;
	FILE *fp;

	if (argc != 2) {
		fprintf(stderr, "usage: %s datafile\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "%s: %s: could not open: %s\n", argv[0],
				argv[1], strerror(errno));
		exit(1);
	}

	for (npres = 0; npres < NPRES && fgets(buf, BUFSIZ, fp) != NULL;
			npres++) {
		sscanf(buf, "%s %s %ld %ld",
				presidents[npres].lastname,
				presidents[npres].firstname,
				&presidents[npres].emp_id,
				&presidents[npres].start_date);
	}
	fclose(fp);

	qsort(presidents, npres, sizeof(struct employee), emp_id_compare);

	printf("Sorted by ID:\n");
	for (i = 0; i < npres; i++) {
		putchar('\n');
		print_employee(&presidents[i]);
	}

	for (;;) {
		printf("Enter ID number: ");
		if (fgets(buf, BUFSIZ, stdin) == NULL)
			break;

		sscanf(buf, "%d\n", &id);
		key.emp_id = id;
		the_pres = (struct employee *)bsearch(&key, presidents, npres,
				sizeof(struct employee), emp_id_compare);

		if (the_pres != NULL) {
			printf("Found: ");
			print_employee(the_pres);
		} else {
			printf("Employee with ID %d not found!\n", id);
		}
	}

	putchar('\n');

	exit(0);
}
