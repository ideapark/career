#include <dirent.h>
#include <fnmatch.h>

/*
 * return nonzero if the file in 'next' should be listed.
 */
static int file_interesting(const struct dirent *next)
{
    register struct ignore_pattern *ignore;

    for (ignore = ignore_pattern; ignore; ignore = ignore->next)
        if (fnmatch(ignore->pattern, next->d_name, FNM_PERIOD) == 0)
            return 0;

    if (
            really_all_files
            || next->d_name[0] != '.'
            || (
                all_files
                && next->d_name[1] != '\0'
                && (next->d_name[1] != '.' || next->d_name[2] != '\0')
               )
       )
        return 1;

    return 0;
}
