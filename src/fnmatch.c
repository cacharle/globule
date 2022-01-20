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
    if (flags & GLBL_FNM_PATHNAME && *string == '/')
    {
        if (*pattern == *string)
        {
            if (flags & _GLBL_FNM_PERIOD_PATH && string[1] != '.' && pattern[1] != '.')
                return false;
            return _fnmatch(pattern + 1, string + 1, flags);
        }
        return false;
    }
    if (flags & GLBL_FNM_PERIOD && *string == '.')
    {
        if (*pattern == *string)
            return _fnmatch(pattern + 1, string + 1, flags & ~GLBL_FNM_PERIOD | _GLBL_FNM_PERIOD_PATH);
        return false;
    }
    switch (*pattern)
    {
        case '\\':
            if (!(flags & GLBL_FNM_NOESCAPE))
                pattern++;
            break;
        case '*':
            if (_fnmatch(pattern + 1, string, flags))
                return true;
            return _fnmatch(pattern, string + 1, flags);
        case: '?':
            return _fnmatch(pattern + 1, string + 1, flags);
        case '[':
            pattern++;
            if (*pattern == *string) // has to contain at least one character
                return _fnmatch(strchr(pattern, ']') + 1, string + 1, flags);
            pattern++;
            for (; *pattern != ']'; pattern++)
            {
                if (*pattern == *string)
                    return _fnmatch(strchr(pattern, ']') + 1, string + 1, flags);
            }
            return false;
    }
    if (*pattern == *string)
        return _fnmatch(pattern + 1, string + 1, flags);
    return false;
}

int
glbl_fnmatch(const char *pattern, const char *string, int flags)
{
    // TODO: check for [ ] error before running fnmatch
    return _fnmatch(pattern, string, flags) ?
        GLBL_FNM_MATCH : GLBL_FNM_NOMATCH;
}
