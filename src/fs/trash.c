#include "fs.h"
#include <stdio.h>
#include <stdlib.h>

void trash_path(char **argv, Metadata *m) {
    if (m->rflag)
        trash_tree(argv, m->eval);
    else
        trash_file(argv, m->eval);
}

void trash_tree(char **argv, int eval) {
    (void)argv;
    printf("TODO: Implement trash_tree()\n");
    exit(eval);
}

void trash_file(char **argv, int eval) {
    (void)argv;
    printf("TODO: Implement trash_file()\n");
    exit(eval);
}
