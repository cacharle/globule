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

Test(glbl_fnmatch, question_mark)
{
    cr_assert_eq(glbl_fnmatch("?", "", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("?", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x?x", "xax", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x?x", "xx", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x???x???x", "x123x456x", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x??x???x", "x123x456x", 0), GLBL_FNM_NOMATCH);
}

Test(glbl_fnmatch, character_classes)
{
    cr_assert_eq(glbl_fnmatch("[zxc]", "z", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[zxc]", "x", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[zxc]", "c", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[zxc]", "j", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x[zxc]x", "xcx", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[zxc]x", "xjx", 0), GLBL_FNM_NOMATCH);
}

Test(glbl_fnmatch, character_classes_range)
{
    cr_assert_eq(glbl_fnmatch("[a-c]", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-c]", "b", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-c]", "c", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-c]", "x", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x[a-c]x", "xcx", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[a-c]x", "xdx", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-G]", "d", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-G]", "b", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-Z]", "H", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-Z]", "I", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-Z]", "c", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-cF-Z]", "C", 0), GLBL_FNM_NOMATCH);
}

Test(glbl_fnmatch, character_classes_complement)
{
    cr_assert_eq(glbl_fnmatch("[!zxc]", "j", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[!zxc]", "z", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!zxc]", "x", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!zxc]", "c", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x[!zxc]x", "xcx", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x[!zxc]x", "xjx", 0), GLBL_FNM_MATCH);
}

Test(glbl_fnmatch, character_classes_ranges_complement)
{
    cr_assert_eq(glbl_fnmatch("[!a-c]", "a", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-c]", "b", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-c]", "c", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-c]", "x", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[!a-c]x", "xcx", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("x[!a-c]x", "xdx", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-G]", "d", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-G]", "b", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-Z]", "H", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-Z]", "I", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-Z]", "c", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[!a-cF-Z]", "C", 0), GLBL_FNM_MATCH);
}

Test(glbl_fnmatch, character_classes_range_with_regular_character)
{
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "b", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "H", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "Z", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "f", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "g", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[fa-cF-Zg]", "j", 0), GLBL_FNM_NOMATCH);
}

Test(glbl_fnmatch, character_classes_first_character_no_meaning)
{
    cr_assert_eq(glbl_fnmatch("x[]]x", "x]x", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[]a]x", "xax", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[]a]x", "x]x", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("x[]a]x", "x[x", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[][!]", "[", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[][!]", "!", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[][!]", "]", 0), GLBL_FNM_MATCH);
}

Test(glbl_fnmatch, character_classes_hypen)
{
    cr_assert_eq(glbl_fnmatch("[-]", "-", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[-]", "a", 0), GLBL_FNM_NOMATCH);
    cr_assert_eq(glbl_fnmatch("[-a]", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-]", "a", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[-a]", "-", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-]", "-", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-c-]", "b", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[a-c-]", "-", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[-a-c]", "b", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[-a-c]", "-", 0), GLBL_FNM_MATCH);
}

Test(glbl_fnmatch, character_classes_hypen_and_square_bracket)
{
    cr_assert_eq(glbl_fnmatch("[]-]", "-", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[]-]", "]", 0), GLBL_FNM_MATCH);
    cr_assert_eq(glbl_fnmatch("[]-]", "x", 0), GLBL_FNM_NOMATCH);
}

Test(glbl_fnmatch, character_classes_error_no_closing_square_bracket)
{
    cr_assert_eq(glbl_fnmatch("[", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_eq(glbl_fnmatch("[[", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_eq(glbl_fnmatch("[]", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_neq(glbl_fnmatch("[]]", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_eq(glbl_fnmatch("[\0]", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_eq(glbl_fnmatch("[a\0]", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
    cr_assert_eq(glbl_fnmatch("[abcd\0]", "", 0), GLBL_FNM_ERROR_MISSING_CLOSING);
}
