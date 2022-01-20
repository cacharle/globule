#ifndef GLOBULE_FNMATCH_H
#define GLOBULE_FNMATCH_H

#define GLBL_FNM_NOESCAPE 0b001
#define GLBL_FNM_PATHNAME 0b010
#define GLBL_FNM_PERIOD   0b100

#define GLBL_FNM_MATCH   0
#define GLBL_FNM_NOMATCH 1

int glbl_fnmatch(const char *pattern, const char *string, int flags);

#endif
