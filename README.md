# Globule

An implementation of `fnmatch` and `glob` in C.


## `fnmatch` — Pattern matching

```c
#include "globule/fnmatch.h"

int glbl_fnmatch(const char *pattern, const char *string, int flags);
```

Matches `string` against a wildcard `pattern` (`*`, `?`, `[...]`).

## `glob` — Pathname expansion

```c
#include "globule/glob.h"

int glbl_glob(const char *pattern, int flags,
              int (*errfunc)(const char *epath, int eerrno),
              glbl_glob_t *pglob);
void glbl_globfree(glbl_glob_t *pglob);
```

Expands `pattern` into matching pathnames.

## Building

Requires [Meson](https://mesonbuild.com/):

```sh
meson setup build
meson compile -C build
```

## Example

```c
glbl_glob_t matches;
glbl_glob("*/*.c", 0, NULL, &matches);
for (int i = 0; i < matches.gl_pathc; i++)
    printf("%s\n", matches.gl_pathv[i]);
glbl_globfree(&matches);
```
