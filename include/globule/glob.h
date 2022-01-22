#ifndef GLOBULE_GLOB_H
#define GLOBULE_GLOB_H

#include <stddef.h>

#define GLBL_GLOB_APPEND 0b00001
#define GLBL_GLOB_DOOFFS 0b00010
#define GLBL_GLOB_ERR 0b00100
#define GLBL_GLOB_MARK 0b01000
#define GLBL_GLOB_NOESCAPE 0b01000
#define GLBL_GLOB_NOSORT 0b01000

#define GLBL_GLOB_SUCCESS 0
#define GLBL_GLOB_ABORTED 1
#define GLBL_GLOB_NOMATCH 2
#define GLBL_GLOB_NOSPACE 3

typedef struct
{
    size_t gl_pathc;
    char **gl_pathv;
    size_t gl_offs;
} glbl_glob_t;

int
glbl_glob(const char *pattern,
          int         flags,
          int (*errfunc)(const char *epath, int eerrrno),
          glbl_glob_t *pglob);
void
glbl_globfree(glbl_glob_t *pglob);

#endif
