#include "globule/glob.h"

int
glbl_glob(const char *pattern,
          int         flags,
          int (*errfunc)(const char *epath, int eerrrno),
          glbl_glob_t *pglob)
{
}

void
glbl_globfree(glbl_glob_t *pglob)
{
}
