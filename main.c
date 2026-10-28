
#include "main.h"

int convert_input_string_to_args(char input_string[], char args[][100]);

int main(void)
{
    char PS1[100] = "minishell$ ";
    char input_string[100];
    char new_prompt[100];
    char args[20][100];
    char cwd[1024];
    int count;
    int i;
    pid_t pid;
    int status;

    system("clear");

    while (1)
    {
        printf("%s", PS1);

        if (fgets(input_string, sizeof(input_string), stdin) == NULL)
        {
            break;
        }

        input_string[strcspn(input_string, "\n")] = '\0';

        if (input_string[0] == '\0')
        {
            continue;
        }

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

        if (count == 0)
        {
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("%s\n", cwd);
            }
            else
            {
                perror("pwd");
            }
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            if (count == 1)
            {
                printf("Usage: cd <directory>\n");
            }
            else if (chdir(args[1]) == -1)
            {
                perror("cd");
            }
        }
        else if (strcmp(args[0], "echo") == 0)
        {
            for (i = 1; i < count; i++)
            {
                printf("%s", args[i]);

                if (i < count - 1)
                {
                    printf(" ");
                }
            }

            printf("\n");
        }
        else
        {
            if (check_external_command(args[0]) == 1)
            {
                pid = fork();

                if (pid == 0)
                {
                    char *argv[20];

                    for (i = 0; i < count; i++)
                    {
                        argv[i] = args[i];
                    }

                    argv[count] = NULL;

                    execvp(argv[0], argv);

                    perror("Command");
                    exit(1);
                }
                else if (pid > 0)
                {
                    waitpid(pid, &status, 0);
                }
                else
                {
                    perror("fork");
                }
            }
            else
            {
                printf("Command not found: %s\n", args[0]);
            }
        }
    }

    return 0;
}
