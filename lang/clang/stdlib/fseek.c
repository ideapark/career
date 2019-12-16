#include <stdio.h>

typedef struct {
	long id;
	double value;
} record;

int main(void)
{
	FILE *fp;
	record cur_rec = (record) { 0, 0.0 };
	int reclength_file = sizeof(record);
	long seek_id = 123L;

	if ((fp = fopen("records", "r")) == NULL) {
		perror("Unable to open records file");
	} else {
		do {
			if (1 > fread(&cur_rec.id, sizeof(long), 1, fp))
				fprintf(stderr,
					"Record with ID %ld not found\n",
					seek_id);
			else	// Skip rest of record
			if (fseek(fp, reclength_file - sizeof(long), 1))
				perror("fseek failed");
		} while (cur_rec.id != seek_id);
	}
	return 0;
}
