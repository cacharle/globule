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

Test(glbl_fnmatch, wildcard)
{
    cr_assert_eq(glbl_fnmatch("*", "", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("*", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("*", "abcdefgh", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("a*", "abcdefgh", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("*h", "abcdefgh", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("a*h", "abcdefgh", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("a*z", "abcdefgh", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("a*b*c", "aIIIbIIIc", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("a*b*c", "aIIIIIIc", 0), GLBL_FNM_NOMATCH);
}
