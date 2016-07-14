#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct employee {
	char lastname[30];
	char firstname[30];
	long emp_id;
	time_t start_date;
};

int emp_name_id_compare(const void *pe1, const void *pe2)
{
	const struct employee *e1, *e2;
	int last, first;

	e1 = (const struct employee *)pe1;
	e2 = (const struct employee *)pe2;

	if ((last = strcmp(e1->lastname, e2->lastname)) != 0)
		return last;

	/* same last name, check first name */
	if ((first = strcmp(e1->firstname, e2->firstname)) != 0)
		return first;

	/* same first name, check ID numbers */
	if (e1->emp_id < e2->emp_id)
		return -1;
	else if (e1->emp_id == e2->emp_id)
		return 0;
	else
		return 1;
}

int emp_seniority_compare(const void *pe1, const void *pe2)
{
	const struct employee *e1, *e2;
	double diff;

	e1 = (const struct employee *)pe1;
	e2 = (const struct employee *)pe2;

	diff = difftime(e1->start_date, e2->start_date);
	if (diff < 0)
		return -1;
	else if (diff > 0)
		return 1;
	else
		return 0;
}

int main(void)
{
#define NPRES 10
	struct employee presidents[NPRES];
	int i, npres;
	char buf[BUFSIZ];

	/* very simple code to read date */
	for (npres = 0; npres < NPRES && fgets(buf, BUFSIZ, stdin) != NULL;
			npres++) {
		sscanf(buf, "%s %s %ld %ld\n",
				presidents[npres].lastname,
				presidents[npres].firstname,
				&presidents[npres].emp_id,
				&presidents[npres].start_date);
	}

	/* sort by name */
	qsort(presidents, npres, sizeof(struct employee), emp_name_id_compare);

	printf("Sorted by name:\n");

	for (i = 0; i < npres; i++) {
		printf("\t%s %s\t%ld\t%s",
				presidents[i].lastname,
				presidents[i].firstname,
				presidents[i].emp_id,
				ctime(&presidents[i].start_date));
	}

	/* sort by seniority */
	qsort(presidents, npres, sizeof(struct employee), emp_seniority_compare);

	printf("Sorted by seniority:\n");

	for (i = 0; i < npres; i++) {
		printf("\t%s %s\t%ld\t%s",
				presidents[i].lastname,
				presidents[i].firstname,
				presidents[i].emp_id,
				ctime(&presidents[i].start_date));
	}

	return 0;
}
