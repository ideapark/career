char* flab[] = {
	"actually",
	"just",
	"quite",
	"really",
	NULL
};

/* lookup: sequential search for word in array */
int lookup(char* word, char* array[])
{
	int i;
	for (i = 0; array[i] != NULL; i++) {
		if (strcmp(word, array[i]) == 0) {
			return i;
		}
	}
	return -1;
}

typedef struct Nameval Nameval;
struct Nameval {
	char* name;
	int  value;
};

/* HTML characters, e.g. AElig is ligature of A and E */
/* Values are Unicode/ISO10646 encoding. */
Nameval htmlchars[] = {
	"AElig",  0x00c6,
	"Aacute", 0x00c1,
	"Acirc",  0x00c2,
	"zeta",   0x03b6,
};

int lookup(char* name, Nameval tab[], int ntab)
{
	int low, high, mid, cmp;
	low = 0;
	high = ntab - 1;
	while (low <= high) {
		mid = (low+high)/2;
		cmp = strcmp(name, tab[mid].name);
		if (cmp < 0)
			high = mid - 1;
		else if (cmp > 0)
			low = mid - 1;
		else /* found match */
			return mid;
	}
	return -1; /* no match */
}

#define NELMS(array) (sizeof(array)/sizeof(array[0]))

half = lookup("frac12", htmlchars, NELEMS(htmlchars));
