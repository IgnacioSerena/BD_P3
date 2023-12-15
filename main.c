#include "types.h"
#include "library.h"
#include "index.h"

int main(int argc, char *argv[])
{
    char str[MAX_STR], *command = NULL, name[MAX_STR], *toks, *info = NULL;
    int id;
    FILE *f;
    Index *index;

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
    strcat(name, ".db");

    f = fopen(name, "w+b");
    if (!f)
        return ERR;

    index = initIndex(100);
    if (!index)
    {
        exit_lib(f, NULL, argv[2]);
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
        if (toks != NULL)
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
                printRec(index, f, 0);
            else if (strcmp(command, "find") == 0)
            {
                id = atoi(info);
                find(index, id, f);
            }
            else
                printf("Write down a valid command\n");
        }
        else
            printf("Write down a valid command\n");
        printf("exit\n");
    }

    exit_lib(f, index, argv[2]);

    return OK;
}
