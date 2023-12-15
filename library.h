#include "types.h"

int add(FILE *f, char *str, Index *index);
int exit_lib(FILE *f, Index *index, IndexDeleted *index_del, char *name);
int find(Index *index, int id, FILE *f);
void printInd(Index *index, FILE *f);
void printRec(Index *index, FILE *f, int num);
int delete(Index *index, IndexDeleted *index_del, FILE *f, int key);