#include "library.h"

int add(FILE *f, char *str)
{
    char *toks, *title, *editorial;
    int id, key;
    size_t size;

    toks = strtok(str, "|");
    id = atoi(toks);
    toks = strtok(str, "|");
    key = atoi(toks);
    title = strtok(str, "|");
    sprintf(title, "|");
    editorial = strtok(str, "|");
    size = sizeof(int) + 16 * sizeof(char) + strlen(title) * sizeof(char) + strlen(editorial) * sizeof(char);
    fwrite(&size, sizeof(size_t), 1, f);
    fwrite(&id, sizeof(int), 1, f);
    fwrite(&key, 16 * sizeof(char), 1, f);
    fwrite(title, strlen(title) * sizeof(char), 1, f);
    fwrite(editorial, strlen(editorial) * sizeof(char), 1, f);

    return OK;
}

int exit_lib(FILE *f)
{
    fclose(f);

    return OK;
}