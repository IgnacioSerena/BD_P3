#include "types.h"
#include "library.h"

int main(int argc, char *argv[])
{
    char str[MAX_STR], *command, *name;
    FILE *f;

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

    printf("Type command and argument/s.\n");

    while(fgets(str, MAX_STR, stdin))
    {
        str[strcspn(str, "\n")] = '\0';
        command = strtok(str, " ");
        printf("%s\n", command);
        
        if (strcmp(command, "exit") == 0)
        {
            exit_lib(f);
            break;
        }
        else if (strcmp(command, "add") == 0)
        {
            add(f, str);
        }
    }

    return OK;
}