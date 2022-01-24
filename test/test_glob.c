#define _DEFAULT_SOURCE
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include "globule/glob.h"

static char filepaths[][1024] = {
    "test1.c",
    "test2.c",
    "test3.c",
    "testfoo.c",
};
static size_t filepaths_len = sizeof(filepaths) / sizeof(filepaths[0]);

static char template[] = "/tmp/globule-glob-XXXXXX";

static void
setup(void)
{
    if (mkdtemp(template) == NULL)
        abort();
    for (size_t i = 0; i < filepaths_len; i++)
    {
        char filename[1024];
        strcpy(filename, filepaths[i]);
        strcpy(filepaths[i], template);
        strcat(filepaths[i], "/");
        strcat(filepaths[i], filename);
        FILE *f = fopen(filename, "r");
        if (f == NULL)
            abort();
        fclose(f);
    }
}

static void
teardown(void)
{
    for (size_t i = 0; i < filepaths_len; i++)
        remove(filepaths[i]);
    remove(template);
}

TestSuite(glbl_glob, .init = setup, .fini = teardown);

Test(glbl_glob, basic)
{
}
