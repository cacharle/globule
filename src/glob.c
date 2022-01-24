#define _XOPEN_SOURCE 500
#include "globule/glob.h"
#include "globule/fnmatch.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

static int
strcmp_ptr(const void *p1, const void *p2)
{
    char *const *s1_ptr = p1;
    char *const *s2_ptr = p2;
    return strcmp(*s1_ptr, *s2_ptr);
}

int
glbl_glob(const char *pattern,
          int         flags,
          int (*errfunc)(const char *epath, int eerrrno),
          glbl_glob_t *pglob)
{
    DIR *dir = opendir(".");
    pglob->gl_pathc = 0;
    pglob->gl_pathv = NULL;
    pglob->gl_offs = 0;

    struct dirent *dirent = NULL;
    while ((dirent = readdir(dir)) != NULL)
    {
        if (glbl_fnmatch(pattern, dirent->d_name, 0) == GLBL_FNM_MATCH)
        {
            pglob->gl_pathc++;
            pglob->gl_pathv =
                realloc(pglob->gl_pathv, pglob->gl_pathc * sizeof(char *));
            pglob->gl_pathv[pglob->gl_pathc - 1] = strdup(dirent->d_name);
        }
    }
    qsort(pglob->gl_pathv, pglob->gl_pathc, sizeof(char *), strcmp_ptr);
    pglob->gl_pathv =
        realloc(pglob->gl_pathv, (pglob->gl_pathc + 1) * sizeof(char *));
    pglob->gl_pathv[pglob->gl_pathc] = NULL;
    return 0;
}

void
glbl_globfree(glbl_glob_t *pglob)
{
    for (size_t i = 0; i < pglob->gl_pathc; i++)
        free(pglob->gl_pathv[i]);
    free(pglob->gl_pathv);
}
