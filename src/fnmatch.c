#include "globule/fnmatch.h"
#include <stdbool.h>
#include <string.h>

static bool
_fnmatch(const char *pattern, const char *string, int flags)
{
    if (*pattern == '\0')
        return *string == '\0';
    if (*string == '\0')
        return strcmp(pattern, "*") == 0;
    if (*pattern == '*')
    {
        if (_fnmatch(pattern + 1, string, flags))
            return true;
        return _fnmatch(pattern, string + 1, flags);
    }
    if (*pattern == *string)
        return _fnmatch(pattern + 1, string + 1, flags);
    return false;
}

int
glbl_fnmatch(const char *pattern, const char *string, int flags)
{
    return _fnmatch(pattern, string, flags) ?
        GLBL_FNM_MATCH : GLBL_FNM_NOMATCH;
}
