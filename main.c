#include "types.h"
#include "library.h"
#include "index.h"

int main(int argc, char *argv[])
{
    char str[MAX_STR], *command = NULL, name[MAX_STR], *name_ind, *toks, *info = NULL;
    FILE *f, *f1;
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

    name_ind = argv[2];
    strcat(name_ind, ".ind");

    index = reload(name_ind);
    if (!index){
        return ERR;
    }

    f = fopen(name, "w");
    if (!f)
        return ERR;
    
    f1 = fopen(name_ind, "w");
    if(!f1)
    {
        exit_lib(f, NULL, NULL);
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
                printInd(index, stdout, f1);
            /*else if (strcmp(command, "printRec") == 0)
                printRec(index, f, index->size - 1);*/
            else if(strcmp(command, "find") == 0)
                find(index, info, f);
            else
                printf("Write down a valid command\n");
        }
        else
            printf("Write down a valid command\n");
        printf("exit\n");
    }

    exit_lib(f, index, f1);

    return OK;
}
