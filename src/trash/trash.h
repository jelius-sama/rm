#ifndef FS_H
#define FS_H

typedef struct {
    int rflag;
    int fflag;
    int wflag;
    int dflag;
    int eval;
} Metadata;

void trash_path(char **, Metadata *);
void trash_tree(char **, Metadata *);
void trash_file(char **, Metadata *);
char *v_realpath(const char *, char *);

#endif // FS_H
