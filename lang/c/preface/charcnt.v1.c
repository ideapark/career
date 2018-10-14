#include <stdio.h>

main()
{
	long nc;

	nc = 0;
	for (nc = 0; getchar() != EOF; ++nc) ;
	printf("%ld\n", nc);
}
