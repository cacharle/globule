#include <criterion/criterion.h>
#include "globule/fnmatch.h"

Test(glbl_fnmatch, string_comparison)
{
    cr_assert_eq(glbl_fnmatch("", "", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("a", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("abc", "abc", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("ab", "abc", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("a", "", 0), GLBL_FNM_NOMATCH);
}
