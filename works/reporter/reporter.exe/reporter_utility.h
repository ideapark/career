/*
 * Copyright (c) Zhou Peng <lockrecv@qq.com>
 */

#ifndef REPORTER_UTILITY_H
#define REPORTER_UTILITY_H

#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#define ARRAY_LENGTH(arr)   (sizeof(arr) / sizeof(arr[0]))

template <class T>
inline std::string to_string(const T &t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

inline std::string tmpname(void)
{
	char tmpfile[] = "temp-XXXXXX";

	close(mkstemp(tmpfile));
	unlink(tmpfile);

	return std::string(tmpfile);
}

inline std::string to_dbname(long l_t)
{
	char buffer[64];
	time_t time = l_t;

	strftime(buffer, 128, "aps-%Y%m%e%H%M%S.db", localtime(&time));

	return std::string(buffer);
}

#define IF_NOT_EQUAL_RETURN(actual, expect) \
{ \
	if ((int64_t)(actual) != (int64_t)(expect)) \
	return; \
}

#define IF_NOT_EQUAL_RETURN_VAL(actual, expect, retval) \
{ \
	if ((int64_t)(actual) != (int64_t)(expect)) \
	return retval; \
}

#define IF_EQUAL_RETURN_VAL(actual, expect, retval) \
{ \
	if ((int64_t)(actual) == (int64_t)(expect)) \
	return retval; \
}

inline uint16_t op_htons(uint16_t x, int cflag)
{
	if (cflag)
		return ((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8));
	else
		return x;
}

inline uint32_t op_htonl(uint32_t x, int cflag)
{
	if (cflag)
		return ((((x) & 0x000000ff) << 24)
			| (((x) & 0x0000ff00) <<  8)
			| (((x) & 0x00ff0000) >>  8)
			| (((x) & 0xff000000) >> 24));
	else
		return x;
}

inline uint64_t op_htonl64(uint64_t x, int cflag)
{
	if (cflag) {
		uint32_t hi, lo;

		lo = (uint32_t)(x & 0xFFFFFFFF);
		x >>= 32;
		hi = (uint32_t)(x & 0xFFFFFFFF);
		x = op_htonl(lo, cflag);
		x <<= 32;
		x |= op_htonl(hi, cflag);

		return x;
	} else {
		return x;
	}
}

#endif /* REPORTER_UTILITY_H */
