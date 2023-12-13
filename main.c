#include "types.h"
#include "library.h"
#include "index.h"

int main(int argc, char *argv[])
{
    char str[MAX_STR], *command = NULL, *name, *toks, *info = NULL;
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

    name = argv[2];
    strcat(name, ".db");

    f = fopen(name, "w");
    if (!f)
        return ERR;

    index = initIndex(100);
    if (!index)
    {
        exit_lib(f, NULL);
        return ERR;
    }

    printf("Type command and argument/s.\n");

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
                printIndex(index);
            else
                printf("Write down a valid command\n");
        }
        else
            printf("Write down a valid command\n");
    }

    exit_lib(f, index);

    return OK;
}
