int gzip_decompress_to_file(const char *input, int output_fd)
{
	if (fstat(input_fd, &stbuf) < 0)
		goto out_close;

	ptr = mmap(NULL, stbuf.st_size, PROT_READ, MAP_PRIVATE, input_fd, 0);
	if (ptr == MAP_FAILED)
		goto out_close;

	if (inflateInit2(&zs, 16 + MAX_WBITS) != Z_OK)
		goto out_unmap;

	/* code omitted ... */
out:
	inflateEnd(&zs);
out_unmap:
	munmap(ptr, stbuf.st_size);
out_close:
	close(input_fd);

	return ret == Z_STREAM_END ? 0 : -1;
}
