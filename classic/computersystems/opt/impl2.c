#include "vec.h"

/*
 * Optimized: eliminate poor performance loop
 */
void combine2(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}
