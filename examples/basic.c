#include <stdio.h>
#include "globule/fnmatch.h"
#include "globule/glob.h"

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

    // printf("%d\n", glbl_fnmatch("[a-]", "-", 0));

    // glbl_fnmatch("*/*", "/foo", GLBL_FNM_PATHNAME);

    glbl_glob_t matches;
    int         ret = glbl_glob("*/*.c", 0, NULL, &matches);
    printf("ret: %d\n", ret);
    for (int i = 0; i < matches.gl_pathc; i++)
    {
        printf("%2d: %s\n", i, matches.gl_pathv[i]);
    }
    glbl_globfree(&matches);
    return 0;
}
