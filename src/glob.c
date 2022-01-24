#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "globule/glob.h"
#include "globule/fnmatch.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

static int
strcmp_ptr(const void *p1, const void *p2)
{
    char *const *s1_ptr = p1;
    char *const *s2_ptr = p2;
    return strcmp(*s1_ptr, *s2_ptr);
}

static int
glob_rec(const char *pattern, char path[PATH_MAX + 1], glbl_glob_t *pglob)
{
    char *dirpath_end = strchr(pattern, '/');
    if (dirpath_end != NULL)
        *dirpath_end = '\0';
    DIR           *dir = opendir(path);
    struct dirent *dirent = NULL;
    while ((dirent = readdir(dir)) != NULL)
    {
        if (glbl_fnmatch(pattern, dirent->d_name, 0) == GLBL_FNM_MATCH)
        {
            if (dirpath_end == NULL)
            {
                pglob->gl_pathc++;
                pglob->gl_pathv =
                    realloc(pglob->gl_pathv, pglob->gl_pathc * sizeof(char *));
                char *match_path =
                    malloc(sizeof(char) * (strlen(path) + strlen(dirent->d_name) +
                                           2));  // +2 for the \0 and the slash
                strcpy(match_path, path);
                strcat(match_path, "/");
                strcat(match_path, dirent->d_name);
                pglob->gl_pathv[pglob->gl_pathc - 1] = match_path;
            }
            else if (dirent->d_type == DT_DIR && strcmp(dirent->d_name, ".") != 0 &&
                     strcmp(dirent->d_name, "..") != 0)
            {
                char *path_end = strchr(path, '\0');
                strcat(path, "/");
                strcat(path, dirent->d_name);
                glob_rec(dirpath_end + 1, path, pglob);
                *path_end = '\0';
            }
        }
    }
    return 0;
}

int
glbl_glob(const char *pattern,
          int         flags,
          int (*errfunc)(const char *epath, int eerrrno),
          glbl_glob_t *pglob)
{
    pglob->gl_pathc = 0;
    pglob->gl_pathv = NULL;
    pglob->gl_offs = 0;
    char path[PATH_MAX + 1] = {'\0'};
    bool absolute_path = pattern[0] == '/';
    if (absolute_path)
        strcpy(path, "/");
    else
        getcwd(path, PATH_MAX);

    char *pattern_dup = strdup(pattern);
    glob_rec(pattern_dup, path, pglob);
    free(pattern_dup);

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
