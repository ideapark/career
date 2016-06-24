#include "vec.h"

/*
 * Optimized: Decrease reference to memory
 */
void combine4(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++)
        acc = acc OP data[i];

    *dest = acc;
}
