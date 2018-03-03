long int simple(long int *xp, long int y)
{
	long int t = *xp + y;
	*xp = t;

	return t;
}
