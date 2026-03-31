#include "bridge.h"
#include "trash.h"
#include <err.h>
#include <errno.h>
#include <libgen.h>
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
            // TODO: Support directories other than just user's home directory
            if (m->wflag) {
                char *abs_path = v_realpath(f, NULL);
                int8_t err = 0;

                if (abs_path) {
                    const char *prefix = "/Users/";
                    const char *next_slash = strchr(abs_path + 7, '/');

                    if (next_slash && strncmp(abs_path, prefix, 7) == 0) {
                        const char *last_item = strrchr(abs_path, '/') + 1;
                        int home_len = next_slash - abs_path;

                        char trash_path[PATH_MAX];
                        snprintf(trash_path, sizeof(trash_path),
                                 "%.*s/.trash/%s", home_len, abs_path,
                                 last_item);

                        if (rename(trash_path, abs_path) != 0) {
                            err = 1;
                            m->eval = 1;
                        }
                    }
                    free(abs_path);
                }

                if (err) {
                    warnx("%s: cannot restore", f);
                }
                continue;
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

        char *err_msg = NULL;
        delete_file_or_directory(f, &err_msg);
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
