/*
 * Call readlink to get the symbolic link vlaue of FILENAME.
 * Return a pointer to that NUL-terminated string in malloc'c
 * storage. If readlink fails, return NULL (caller may use
 * errno to diagnose). If realloc fails, or if the link value
 * is longer than SIZE_MAX :-), give a diagnostic and exit.
 */

char *xreadlink(const char *filename)
{
	/* The initial buffer size for the link value. A power of 2
	   detects arithmetic overflow earlier, but is no required. */
	size_t buf_size = 128;

	while (1) {
		char *buffer = xmalloc(buf_size);
		ssize_t link_length = readlink(filename, buffer, buf_size);

		if (link_length < 0) {
			int saved_errno = errno;
			free(buffer);
			errno = saved_errno;
			return NULL;
		}

		if ((size_t)link_length < buf_size) {
			buffer[link_length] = '\0';
			return buffer;
		}

		free(buffer);
		buf_size *= 2;
		if (SSIZE_MAX < buf_size
				|| (SIZE_MAX/2 < SSIZE_MAX && buf_size == 0))
			xalloc_die();
	}
}
