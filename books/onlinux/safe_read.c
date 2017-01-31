#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>


/**
 * read (write) up to COUNT bytes at buf from (to) descriptor fd,
 * retrying if interrupted. return the actual number of bytes
 * read (written), zero for EOF, or SAFE_READ_ERROR(SAFE_WRITE_ERROR)
 * upon error.
 */
size_t safe_write(int fd, void *buf, size_t count)
{
        ssize_t result;

        /* POSIX limits count to SSIZE_MAX, but we limit it further, requiring
         * that count <= INT_MAX, to avoid triggering a bug in Tru64 5.1
         * When decreasing count, keep the file pointer block-aligned.
         * Note that in any case, read (write) may succeed, yet read (write)
         * fewer than count bytes, so the caller must be prepared to handle
         * partial results.
         */
        if (count > INT_MAX)
                count = INT_MAX & ~8191;

        do {
                result = write(fd, buf, count);
        } while (result < 0 && IS_EINTR(errno));

        return (size_t)result;
}


#define TEMP_FAILURE_RETRY(expression)                                \
        (                                                             \
                __extension__                                         \
                ({                                                    \
                        long int __result;                            \
                        do {                                          \
                                __result = (long int) (expression);   \
                        } while (__result == -1L && errno == EINTR);  \
                        __result;                                     \
                })                                                    \
                )


size_t safe_read(int fd, void *buf, size_t count)
{
        ssize_t result;

        if (count > INT_MAX)
                count = INT_MAX & ~8191;

        result = TEMP_FAILURE_RETRY(read(fd, buf, count));

        return (size_t)result;
}
