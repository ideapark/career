#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
	int integer;
	char string[24];
} RECORD;

#define NRECORDS (10)

void display_record()
{
	int i;
	FILE *fp;
	RECORD record;

	fp = fopen("records.dat", "r+");
	for (i = 0; i < NRECORDS; i++) {
		fread(&record, sizeof(record), 1, fp);
		printf("%3d: %s\n", record.integer, record.string);
	}
	fclose(fp);
	printf("\n");
}

int main(void)
{
	int i, f;
	FILE *fp;
	RECORD record, *mapped;

	fp = fopen("records.dat", "w+");
	for (i = 0; i < NRECORDS; i++) {
		record.integer = i;
		sprintf(record.string, "RECORD-%d", i);
		fwrite(&record, sizeof(record), 1, fp);
	}
	fclose(fp);
	display_record();

	fp = fopen("records.dat", "r+");
	fseek(fp, 4*sizeof(record), SEEK_SET);
	fread(&record, sizeof(record), 1, fp);

	record.integer = 143;
	sprintf(record.string, "RECORD-%d", record.integer);

	fseek(fp, 4*sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp);
	fclose(fp);
	display_record();

	f = open("records.dat", O_RDWR);
	mapped = (RECORD *)mmap(0, NRECORDS*sizeof(record), PROT_READ|PROT_WRITE,
			MAP_SHARED, f, 0);
	mapped[4].integer = 243;
	sprintf(mapped[4].string, "RECORD-%d", mapped[4].integer);

	msync((void*)mapped, NRECORDS*sizeof(record), MS_ASYNC);
	munmap((void*)mapped, NRECORDS*sizeof(record));
	close(f);
	display_record();

	return 0;
}
