/* OPT: Code Motion */

/* Convert string to lower case: slow */
void lower1(char *s)
{
  int i;

  for (i = 0; i < strlen(s); i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] -= ('A' - 'a');
    }
  }
}

/* Convert string to lower case: faster */
void lower2(char *s)
{
  int i;
  int len = strlen(s);

  for (i = 0; i < len; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      s[i] -= ('A' - 'a');
    }
  }
}

/* Implementation of library function strlen */
/* Compute length of string */
size_t strlen(const char *s)
{
  int length = 0;
  while (*s != '\0') {
    s++;
    length++;
  }
  return length;
}
