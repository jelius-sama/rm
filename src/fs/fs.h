#ifndef FS_H
#define FS_H

typedef struct {
    int rflag;
    int fflag;
    int eval;
} Metadata;

void trash_path(char **, Metadata *);
void trash_tree(char **, int);
void trash_file(char **, int);

#endif // FS_H
