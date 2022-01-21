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
    // if (flags & GLBL_FNM_PATHNAME && *string == '/')
    // {
    //     if (*pattern == *string)
    //     {
    //         if (flags & _GLBL_FNM_PERIOD_PATH && string[1] != '.' && pattern[1] !=
    //         '.')
    //             return false;
    //         return _fnmatch(pattern + 1, string + 1, flags);
    //     }
    //     return false;
    // }
    // if (flags & GLBL_FNM_PERIOD && *string == '.')
    // {
    //     if (*pattern == *string)
    //         return _fnmatch(pattern + 1, string + 1, flags & ~GLBL_FNM_PERIOD |
    //         _GLBL_FNM_PERIOD_PATH);
    //     return false;
    // }
    switch (*pattern)
    {
    // case '\\':
    //     if (!(flags & GLBL_FNM_NOESCAPE))
    //         pattern++;
    //     break;
    case '*':
        if (_fnmatch(pattern + 1, string, flags))
            return true;
        return _fnmatch(pattern, string + 1, flags);
    case '?':
        return _fnmatch(pattern + 1, string + 1, flags);
    case '[':
        pattern++;
        bool complement = *pattern == '!';
        if (complement)
            pattern++;
        const char *closing = strchr(pattern + 1, ']') + 1;
        if (*pattern == *string)  // has to contain at least one character
            return !complement ? _fnmatch(closing, string + 1, flags) : false;
        pattern++;
        for (; *pattern != ']'; pattern++)
        {
            if (pattern[0] == '-')
            {
                char range_start = pattern[-1];
                char range_end = pattern[1];
                if (*string >= range_start && *string <= range_end)
                    return !complement ? _fnmatch(closing, string + 1, flags)
                                       : false;
                pattern++;
            }
            else if (*pattern == *string)
                return !complement ? _fnmatch(closing, string + 1, flags) : false;
        }
        return !complement ? false : _fnmatch(closing, string + 1, flags);
    }
    if (*pattern == *string)
        return _fnmatch(pattern + 1, string + 1, flags);
    return false;
}

int
glbl_fnmatch(const char *pattern, const char *string, int flags)
{
    bool in_class = false;
    for (size_t i = 0; pattern[i] != '\0'; i++)
    {
        if (pattern[i] == '[')
        {
            i++;
            if (pattern[i] == '\0')
                return GLBL_FNM_ERROR_MISSING_CLOSING;
            i++;
            if (pattern[i] == '\0')
                return GLBL_FNM_ERROR_MISSING_CLOSING;
            in_class = true;
        }
        if (pattern[i] == ']')
            in_class = false;
    }
    if (in_class)
        return GLBL_FNM_ERROR_MISSING_CLOSING;
    return _fnmatch(pattern, string, flags) ? GLBL_FNM_MATCH : GLBL_FNM_NOMATCH;
}
