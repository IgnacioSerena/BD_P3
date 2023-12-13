#include "library.h"
#include "index.h"

int add(FILE *f, char *str, Index *index)
{
    char *toks, *title, *editorial, *key;
    int id;
    size_t size;

    toks = strtok(str, "|");
    id = atoi(toks);
    toks = strtok(NULL, "|");
    key = strdup(toks);
    toks = strtok(NULL, "|");
    title = toks;
    toks = strtok(NULL, "|");
    editorial = toks;

    printf("%s %s\n", title, editorial);

    size_t offset = ftell(f); // Obtiene el offset actual al final del archivo
    size = sizeof(int) + 16 * sizeof(char) + strlen(title) + strlen(editorial);

    if(index->size > 0)
    {
        printf("1\n");
        offset += index->entries[index->size - 1].offset;
    }

    if (binarySearch(index, key) == -1)
    {
        if (insertEntry(index, key, offset, size) == ERR)
            return ERR;
    }
    else
    {
        printf("Record with BookID=%d exists\n", id);
        return OK;
    }

    fwrite(&size, sizeof(size_t), 1, f);
    fwrite(&id, sizeof(int), 1, f);
    fwrite(&key, 16 * sizeof(char), 1, f);
    fwrite(title, strlen(title) + 1, 1, f);
    fwrite(editorial, strlen(editorial) + 1, 1, f);

    printf("Record with BookID=%d has been added to the database\n", id);

    return OK;
}

int exit_lib(FILE *f, Index *index)
{
    freeIndex(index);
    fclose(f);

    return OK;
}
