
#include "minishell.h"

int convert_input_string_to_args(char input_string[], char args[][100]);

int main(void)
{
    char PS1[100] = "minishell$ ";
    char input_string[100];
    char new_prompt[100] = "";
    char args[20][100];
    int count;
    int i;

    system("clear");

    while (1)
    {
        printf("%s", PS1);

        if (scanf("%99[^\n]", input_string) != 1)
        {
            if (feof(stdin))
            {
                break;
            }

            getchar();
            continue;
        }

        getchar();

        if (input_string[0] == ' ')
        {
            printf("Input should not start with a space.\n");
            continue;
        }

        if (strncmp(input_string, "PS1=", 4) == 0)
        {
            strcpy(new_prompt, input_string + 4);

            if (new_prompt[0] != '\0' &&
                strchr(new_prompt, ' ') == NULL)
            {
                strcpy(PS1, new_prompt);
            }
            else
            {
                printf("Invalid prompt string.\n");
            }

            continue;
        }

        count = convert_input_string_to_args(input_string, args);

        for (i = 0; i < count; i++)
        {
            printf("args[%d] = %s\n", i, args[i]);
        }
    }

    return 0;
}


