/*
 * A Regular Expression Matcher
 *
 * https://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
 */

int matchstar(int c, char *regexp, char *text);
int matchhere(char *regexp, char *text);

/*
 * match: search for regexp anywhere in text
 *
 *    c    matches any literal character c
 *    .    matches any single character
 *    ^    matches the beginning of the input string
 *    $    matches the end of the input string
 *    *    matches zero or more occurrences of the previous character
 */
int match(char *regexp, char *text) {
  if (regexp[0] == '^')
    return matchhere(regexp+1, text);

  /* must look even if string is empty */
  do {
    if (matchhere(regexp, text))
      return 1;
  } while (*text++ != '\0');

  return 0;
}

/*
 * matchhere: search for regexp at beginning of text
 */
int matchhere(char *regexp, char *text) {
  if (regexp[0] == '\0')
    return 1;
  if (regexp[1] == '*')
    return matchstar(regexp[0], regexp+2, text);
  if (regexp[0] == '$' && regexp[1] == '\0')
    return *text == '\0';
  if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
    return matchhere(regexp+1, text+1);
  return 0;
}

/*
 * matchstar: search for c*regexp at beginning of text
 */
int matchstar(int c, char *regexp, char *text) {
  /* a * matches zero or more instances */
  do {
    if (matchhere(regexp, text))
      return 1;
  } while (*text != '\0' && (*text++ == c || c == '.'));

  return 0;
}
