int switch_eg(int x, int n) {
  int result = x;

  switch (x) {
  case 100:
    result += 13;
    break;

  case 102:
    result += 10;
    /* Fall through */

  case 103:
    result += 11;
    break;

  case 104:
  case 106:
    result += result;
    break;

  default:
    result = 0;
  }

  return result;
}

/* GCC JUMP TABLE IMPLEMENTATION */
int switch_eg_impl(int x, int n) {
  /* Table of code pointers */
  static void *jt[7] = {
    &&loc_A,     /* 0 */
    &&loc_def,   /* 1 */
    &&loc_B,     /* 2 */
    &&loc_C,     /* 3 */
    &&loc_D,     /* 4 */
    &&loc_def,   /* 5 */
    &&loc_D      /* 6 */
  };

  unsigned index = n - 100;
  int result;

  if (index > 6)
    goto loc_def;

  /* Multiway branch */
  goto *jt[index];

 loc_def: /* Default case */
  result = 0;
  goto done;

 loc_C: /* Case 103 */
  result = x;
  goto rest;

 loc_A: /* Case 100 */
  result = x * 13;
  goto done;

 loc_B: /* Case 102 */
  result = x + 10;
  /* Fall through */

 rest:  /* Finish case 103 */
  result += 11;
  goto done;

 loc_D:  /* Cases 104, 106 */
  result = x * x;
  /* Fall through */

 done:
  return result;
}
