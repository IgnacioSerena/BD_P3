#include "types.h"

int add(FILE *f, char *str, Index *index);
int exit_lib(FILE *f, Index *index, FILE *f1);
int find(Index *index, int id, FILE *f);
void printInd(Index *index, FILE *f, FILE *f1);
void printRec(Index *index, FILE *f, int num);