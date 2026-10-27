// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// int main()
// {
//     char PS1[100]="minishell$:";
//     char input_string[100];
//     system("clear");
//     printf("%s",PS1);
//     //fgets(input_string,sizeof(input_string),stdin);
//     scanf("%[^\n]",input_string);
//     if(strstr(input_string,"PS1=")!=0)
//     {
//         printf("Input should not start with a space.\n");
//     }
//     if(strchr(input_string,' ')!=NULL)
//     {
//         printf("Input contains a space.\n");
//     }
//     else{
//         printf("Input does not contain a space.\n");
//     }
//     strcpy(PS1,input_string);
// }




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char PS1[100] = "minishell$:";
    char input_string[100];
    char new_prompt[100];
    char line[100];
    char *args[20];
    char *External[100];
    char *token;
    FILE *fp;
    int i, cmd_type, count = 0;
    system("clear");
    printf("%s",PS1);
    // Read input string
    scanf("%[^\n]", input_string);
    // Check whether input starts with a space
    if(input_string[0] == ' ')
    {
        printf("Input should not start with a space.\n");
        return 0;
    }
    // Check whether input contains a space
    if(strchr(input_string, ' ') != NULL)
    {
        printf("Input contains a space.\n");
    }
    else
    {
        printf("Input does not contain a space.\n");
        // Copy input string to prompt string
        strcpy(PS1, input_string);
    }
    // Check whether user wants to change the prompt
    if(strncmp(input_string, "PS1=", 4) == 0)
    {
        strcpy(new_prompt, input_string + 4);
        strcpy(PS1, new_prompt);
    }
    // Read external commands from external.txt
    fp = fopen("external.txt", "r");
    if(fp == NULL)
    {
        printf("Unable to open external.txt\n");
        return 1;
    }
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line,"\n")]='\0';

        if(line[0] == '\0')
            continue;

        External[count] = malloc(strlen(line) + 1);

        if(External[count] == NULL)
        {
            printf("Memory allocation failed\n");
            fclose(fp);
            return 1;
        }
        strcpy(External[count], line);
        count++;
        if(count == 100)
            break;
    }
    External[count] = NULL;
    fclose(fp);
    // Convert input string into words
    i = 0;
    token = strtok(input_string, " ");
    while(token != NULL && i < 19)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    // Check command type
    cmd_type = 0;
    if(args[0] != NULL)
    {
        // Check built-in commands
        if(strcmp(args[0], "cd") == 0 || strcmp(args[0], "pwd") == 0 || strcmp(args[0], "echo") == 0 || strcmp(args[0], "exit") == 0)
        {
            cmd_type = 1;
        }
        else
        {
            // Check external commands
            for(i = 0; i < count; i++)
            {
                if(strcmp(args[0], External[i]) == 0)
                {
                    cmd_type = 2;
                    break;
                }
            }
        }
    }
    if(cmd_type == 1)
    {
     printf("Built in command\n");
    }
    else if(cmd_type == 2)
    {
        printf("External command\n");
    }
    else
    {
        printf("No command found\n");
    }
    //Free allocated memory
    for(i = 0; i < count; i++)
    {
        free(External[i]);
    }
    return 0;
}
