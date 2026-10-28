#include "main.h"

int check_external_command(char *command)
{
    FILE *fp;
    char line[100];

    fp = fopen("external.txt", "r");

    if (fp == NULL)
    {
        perror("external.txt");
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        /* Remove newline and Windows carriage-return characters */
        line[strcspn(line, "\r\n")] = '\0';

        if (strcmp(line, command) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}