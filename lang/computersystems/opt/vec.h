#ifndef _VEC_H_
#define _VEC_H_

#define IDENT   0
#define OP      +

typedef int data_t;

typedef struct {
  long int len;
  data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long int len);
data_t *get_vec_start(vec_ptr v);
int get_vec_element(vec_ptr v, long int index, data_t *dest);
long int vec_length(vec_ptr v);

#endif // _VEC_H_
