#include "vec.h"

/*
 * Opmitized: unroll loop
 */
void combine5(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);
    long int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < limit; i += 2) {
        acc = (acc OP data[i]) OP data[i+1];
    }

    for (; i < length; i++) {
        acc = acc OP data[i];
    }

    *dest = acc;
}
