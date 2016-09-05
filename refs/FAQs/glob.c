int match(const char *pat, const char *str)
{
	switch (*path) {
	case '\0':
		return !*str;
	case '*':
		return match(pat+1, str) || *str && match(pat, str+1);
	case '?':
		return *str && match(pat+1, str+1);
	default:
		return *pat == *str && match(pat+1, str+1);
	}
}
