#include "bridge.h"
#include "trash.h"
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void trash_path(char **argv, Metadata *m) {
    if (m->rflag)
        trash_tree(argv, m);
    else
        trash_file(argv, m);
}

void trash_tree(char **argv, Metadata *m) {
    (void)argv;
    printf("TODO: Implement trash_tree()\n");
    exit(m->eval);
}

void trash_file(char **argv, Metadata *m) {
    char *f;
    struct stat sb;

    while ((f = *argv++) != NULL) {
        if (lstat(f, &sb)) {
            if (m->wflag) {
                // sb.st_mode = S_IFWHT | S_IWUSR | S_IRUSR;
                printf("TODO: Implement restoring from trash\n");
            } else {
                if (!m->fflag || errno != ENOENT) {
                    warn("%s", f);
                    m->eval = 1;
                }
                continue;
            }
        } else if (m->wflag) {
            warnx("%s: %s", f, strerror(EEXIST));
            m->eval = 1;
            continue;
        }

        if (S_ISDIR(sb.st_mode) && !m->dflag) {
            warnx("%s: is a directory", f);
            m->eval = 1;
            continue;
        }

        char absolute_path[PATH_MAX];
        if (realpath(f, absolute_path) == NULL) {
            if (!m->fflag) {
                warn("%s", f);
                m->eval = 1;
            }
            continue;
        }

        char *err_msg = NULL;
        delete_file_or_directory(absolute_path, &err_msg);
        if (err_msg != NULL) {
            warnx("%s\n", err_msg);
            m->eval = 1;
            free(err_msg);
            continue;
        }
        m->eval = 0;
    }

    exit(m->eval);
}
