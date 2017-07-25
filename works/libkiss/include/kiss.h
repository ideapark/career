/*
 * Copyright (c) 2014 - 2015, Zhou Peng
 *        ALL RIGHTS RESERVED
 */

#ifndef KISS_H
#define KISS_H

/*
 * boolean values
 */
typedef enum {
	false = 0,
	true  = 1,
} bool;

/*
 * [begin, end)
 */
struct range {
	unsigned short begin; /* include */
	unsigned short end;   /* exclude */
};

/*
 * @brief find substring
 *
 * @arg str
 * @arg match
 * @arg range
 */
bool grep(const char *str, const char *match, struct range *range);

/*
 * @brief cut substring
 *
 * @arg str
 * @arg cut
 */
int cut(char *str, const char *cut);

/*
 * @brief count two string different characters
 *
 * @arg str1
 * @arg str2
 */
int diff(const char *str1, const char *str2);

/*
 * @brief sort string characters
 *
 * @arg str
 */
void sort(char *str);

/*
 * @brief uniq string characters
 *
 * @arg str
 */
int uniq(char *str);

/*
 * @brief replace substring with another
 *
 * @arg match
 * @arg replace
 */
int sed(char *str, const char *match, const char *replace);

#endif /* KISS_H */
