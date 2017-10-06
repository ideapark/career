/* testmalloc: return NULL after 10 calls */
void* testmalloc(size_t n)
{
	static int count = 0;

	if (++count > 10)
		return NULL;
	else
		return malloc(n);
}
