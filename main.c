#include "types.h"
#include "library.h"
#include "index.h"

int main(int argc, char *argv[])
{
    char str[MAX_STR], *command = NULL, name[MAX_STR], *toks, *info = NULL;
    FILE *f;
    Index *index;
    IndexDeleted *index_del;
    FILE *find_2, *fdel;
    char nind[MAX_STR], ndel[MAX_STR];
    int i, id;

    if (argc < 3)
    {
        printf("Missing argument");
        return ERR;
    }
    else if (strcmp(argv[1], "first_fit") != 0 && strcmp(argv[1], "best_fit") != 0 && strcmp(argv[1], "last_fit") != 0)
    {
        printf("Unknown search strategy %s", argv[1]);
        return ERR;
    }

    strcpy(name, argv[2]);
    strcpy(nind, argv[2]);
    strcpy(ndel, argv[2]);
    strcat(name, ".db");
    strcat(nind, ".ind");
    strcat(ndel, ".del");

    find_2 = fopen(nind, "a+b");
    if (!find_2)
        return ERR;

    fdel = fopen(ndel, "w+b");
    if (!fdel)
    {
        fclose(find_2);
        return ERR;
    }


    index = reload(nind);
    if (!index){
        return ERR;
    }

    index_del = initIndexDeleted(100);
    if (!index_del){
        freeIndex(index);
        return ERR;
    }
    

    f = fopen(name, "w");
    if (!f){
        exit_lib(NULL, index, NULL);
        return ERR;
    }

    

    printf("Type command and argument/s.\n");
    printf("exit\n");

    while (fgets(str, MAX_STR, stdin))
    {
        toks = strtok(str, " ");
        command = toks;
        command[strcspn(str, "\n")] = '\0';

        toks = strtok(NULL, "\n");
        if(toks != NULL)
            info = toks;

        if (command)
        {
            if ((strcmp(command, "exit") == 0))
                break;
            else if (strcmp(command, "add") == 0)
            {
                if (add(f, info, index) == ERR)
                    printf("Error adding book\n");
            }
            else if (strcmp(command, "printInd") == 0)
                printInd(index, stdout);
            else if (strcmp(command, "printRec") == 0)
                printRec(index, f, index->size - 1);
            else if(strcmp(command, "find") == 0){
                id = atol(info);
                find(index, id, f);
            }
            else
                printf("Write down a valid command\n");
        }
        else
            printf("Write down a valid command\n");
        printf("exit\n");
    }

    for (i = 0; i < index->size; i++)
    {
        fwrite(&index->entries[i].key, sizeof(int), 1, find_2);
        fwrite(&index->entries[i].offset, sizeof(size_t), 1, find_2);
        fwrite(&index->entries[i].size, sizeof(size_t), 1, find_2);
        fwrite(&index->entries[i].key, sizeof(int), 1, fdel);
        fwrite(&index->entries[i].offset, sizeof(size_t), 1, fdel);
        fwrite(&index->entries[i].size, sizeof(size_t), 1, fdel);
    }


    fclose(find_2);
    fclose(fdel);
    exit_lib(f, index, index_del);

    return OK;
}
