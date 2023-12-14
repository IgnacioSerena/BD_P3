#include "library.h"
#include "index.h"

int add(FILE *f, char *str, Index *index)
{
    char *toks, *title, *isbn;
    int id;
    size_t size;

    toks = strtok(str, "|");
    id = atoi(toks);
    toks = strtok(NULL, "|");
    isbn = toks;
    toks = strtok(NULL, "\\");
    title = toks;

    fseek(f, 0, SEEK_END);
    size_t offset = ftell(f) - index->size; // Obtiene el offset actual al final del archivo
    size = sizeof(int) + strlen(isbn) + strlen(title);

    if (binarySearch(index, id) == -1)
    {
        if (insertEntry(index, id, offset, size) == ERR)
            return ERR;
    }
    else
    {
        printf("Record with BookID=%d exists\n", id);
        return OK;
    }

    fwrite(&size, sizeof(size_t), 1, f);
    fwrite(&id, sizeof(int), 1, f);
    fwrite(isbn, 16 * sizeof(char), 1, f);
    fwrite(title, strlen(title) + 1, 1, f);

    printf("Record with BookID=%d has been added to the database\n", id);

    return OK;
}

int exit_lib(FILE *f, Index *index)
{
    freeIndex(index);
    fclose(f);

    return OK;
}
