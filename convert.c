
#include "main.h"

int convert_input_string_to_args(char input_string[], char args[][100])
{
    int i = 0;
    char *token;

    token = strtok(input_string, " \t\n");

    while (token != NULL && i < 20)
    {
        strcpy(args[i], token);
        i++;
        token = strtok(NULL, " \t\n");
    }

    return i;
}
