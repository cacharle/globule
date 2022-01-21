#include <stdio.h>
#include "globule/fnmatch.h"

int
main(void)
{
    // printf("%d\n", glbl_fnmatch("", "", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b", "ab", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b", "acccccccccb", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b", "acasdfasdf", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b", "acasdfbasdfb", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b*c", "afbc", 0) == GLBL_FNM_MATCH);
    // printf("%d\n", glbl_fnmatch("a*b*c", "afbdd", 0) == GLBL_FNM_MATCH);

    printf("%d\n", glbl_fnmatch("[\0]", "z", 0));

    return 0;
}
