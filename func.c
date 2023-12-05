#include "func.h"

int add(FILE *f, char *str)
{
    int id, i = 0;
    char *toks;
    size_t size;
    Book *b;

    toks = strtok(str, "|");
    b->id = atoi(toks);
    toks = strtok(str, "|");
    b->key = atoi(toks);
    b->title = strtok(str, "|");
    sprintf(b->title, "|");
    b->editorial = strtok(str, "|");
    size = sizeof(int) + 16 * sizeof(char) + strlen(b->title) * sizeof(char) + strlen(b->editorial) * sizeof(char);
    fwrite(size, sizeof(size_t), 1, f);
    fwrite(b->id, sizeof(int), 1, f);
    fwrite(b->key, 16 * sizeof(char), 1, f);
    fwrite(b->key, strlen(b->title) * sizeof(char), 1, f);
    fwrite(b->key, strlen(b->editorial) * sizeof(char), 1, f);

    return 0;
}