#include <stdlib.h>
#include "vec.h"

/* Create vector of specified length */
vec_ptr new_vec(long int len)
{
  /* allocate header structure */
	vec_ptr result = (vec_ptr)malloc(sizeof(vec_rec));

	if (!result)
		return NULL; /* Couldn't allocate storage */

	result->len = len;

  /* Allocate array */
	if (len > 0) {
		data_t *data = (data_t *)calloc(len, sizeof(data_t));
		if (!data) {
			free((void *)result);
			return NULL; /* Couldn't allocate storage */
		}
		result->data = data;
	} else
		result->data = NULL;

	return result;
}

data_t *get_vec_start(vec_ptr v)
{
	return v->data;
}

/*
 * Retrieve vector element and store at dest.
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long int index, data_t *dest)
{
	if (index < 0 || index >= v->len)
		return 0;

	*dest = v->data[index];

	return 1;
}

/* Return length of vector */
long int vec_length(vec_ptr v)
{
	return v->len;
}
