#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *v_realpath(const char *path, char *resolved_path) {
    if (!path)
        return NULL;

    char buf[PATH_MAX];
    char *out = resolved_path ? resolved_path : malloc(PATH_MAX);
    if (!out)
        return NULL;

    if (path[0] != '/') {
        if (!getcwd(buf, PATH_MAX)) {
            if (!resolved_path)
                free(out);
            return NULL;
        }
        strcat(buf, "/");
        strcat(buf, path);
    } else {
        strncpy(buf, path, PATH_MAX - 1);
        buf[PATH_MAX - 1] = '\0';
    }

    char *stack[PATH_MAX / 2];
    int top = 0;
    char *saveptr;
    char *token = strtok_r(buf, "/", &saveptr);

    while (token) {
        if (strcmp(token, "..") == 0) {
            if (top > 0)
                top--; // Pop
        } else if (strcmp(token, ".") != 0) {
            stack[top++] = token; // Push
        }
        token = strtok_r(NULL, "/", &saveptr);
    }

    if (top == 0) {
        strcpy(out, "/");
    } else {
        out[0] = '\0';
        for (int i = 0; i < top; i++) {
            strcat(out, "/");
            strcat(out, stack[i]);
        }
    }

    return out;
}
