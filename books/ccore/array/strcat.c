char* strcat(char *s1, const char *s2)
{
	char *rtnPtr = s1;
	while (*s1 != '\0')
		++s1;
	while ((*s1++ = *s2++) != '\0')
		;
	return rtnPtr;
}
