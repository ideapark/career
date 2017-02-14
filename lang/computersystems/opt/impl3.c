#include "vec.h"

/*
 * Optimized: cut down function calls
 */
void combine3(vec_ptr v, data_t *dest)
{
	long int i;
	long int length = vec_length(v);
	data_t *data = get_vec_start(v);

	*dest = IDENT;
	for (i = 0; i < length; i++)
		*dest = *dest OP data[i];
}
