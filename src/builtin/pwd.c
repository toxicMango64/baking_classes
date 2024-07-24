
#include "../inc/minishell.h"


#define BUFFER_SIZE 42

void execute_pwd() 
{
    char buffer[BUFFER_SIZE];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
        printf("%s\n", buffer);
    else
        printf("error");
}

void parse_pwd(char *command)
{
    if (strcmp(command, "pwd") == 0)
        execute_pwd();
    else
        printf("I dont know the recipe: %s\n", command);
}

// int main() 
// {
//     char *input;

//     while (1) 
//     {

//         input = readline("baking_classes> ");

//         if (input == NULL)
//             break;
//         if (strcmp(input, "exit") == 0) 
//         {
//             free(input);
//             break;
//         }
//         parse_pwd(input);
//         free(input);
//     }
//     return (0);
// }

