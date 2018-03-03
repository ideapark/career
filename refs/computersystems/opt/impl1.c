#include "vec.h"

/*
 * simple implementation
 */
void combine1(vec_ptr v, data_t *dest)
{
	long int i;

	*dest = IDENT;
	for (i = 0; i < vec_length(v); i++) {
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}
