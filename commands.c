
#include "main.h"

int is_builtin_command(char **args)
{
    if (args[0] == NULL)
    {
        return 0;
    }

    if (strcmp(args[0], "exit") == 0 ||
        strcmp(args[0], "pwd") == 0)
    {
        return 1;
    }

    return 0;
}
