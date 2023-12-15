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
    size_t offset = ftell(f); // Obtiene el offset actual al final del archivo
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
    fwrite(title, strlen(title), 1, f);

    printf("Record with BookID=%d has been added to the database\n", id);

    return OK;
}

int exit_lib(FILE *f, Index *index, char *name)
{
    FILE *find, *fdel;
    char nind[MAX_STR], ndel[MAX_STR];
    int i;

    strcpy(nind, name);
    strcpy(ndel, name);
    strcat(nind, ".ind");
    strcat(ndel, ".del");

    find = fopen(nind, "w+b");
    if(!find)
        return ERR;
    
    fdel = fopen(ndel, "w+b");
    if(!fdel)
    {
        fclose(find);
        return ERR;
    }

    for (i = 0; i < index->size; i++)
    {
        fwrite(&index->entries[i].key, sizeof(int), 1, find);
        fwrite(&index->entries[i].offset, sizeof(size_t), 1, find);
        fwrite(&index->entries[i].size, sizeof(size_t), 1, find);
    }


    fclose(find);
    fclose(fdel);
    freeIndex(index);
    fclose(f);

    return OK;
}

int find(Index *index, int id, FILE *f)
{
    char isbn[MAX_STR], title[MAX_STR];
    int pos;
    size_t tam_title;

    pos = binarySearch(index, id);
    if (pos == -1)
        printf("Record with bookId=%d does not exist\n", id);
    else
    {
        fseek(f, index->entries[pos].offset + 8, SEEK_SET);
        fread(&id, sizeof(int), 1, f);
        fread(isbn, 16 * sizeof(char), 1, f);
        isbn[16] = '\0';
        tam_title = index->entries[pos].size - (sizeof(id) + 16 * sizeof(char));
        fread(title, tam_title, 1, f);
        title[tam_title] = '\0';
        printf("%d|%s|%s\n", id, isbn, title);
    }

    return OK;
}

void printInd(Index *index, FILE *f)
{
    printIndex(index, f);
}

void printRec(Index *index, FILE *f, int num)
{
    if(index->size != num)
    {
        find(index, index->entries[num++].key, f);
        printRec(index, f, num);
    }
}

int delete(Index *index, FILE *f, int key)
{
    int pos = binarySearch(index, key);
    if(pos != -1)
    {

        printf(" Record with bookId=%d has been deleted", key);
    }
    else 
        printf("Record with bookId=%d does not exist\n", key);  

    return OK;
}
