#include "../include/builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * @brief Executes a built-in command with the given arguments.
 * @param command The built-in command to execute.
 * @param args The arguments for the command.
 */

int is_builtin(const char* command)
{
    if (strcmp(command, "cd") == 0 ||
       
        strcmp(command, "exit") == 0 ||
        
        strcmp(command, "help") == 0)
    {
        return 1;
    }
    return 0;
}

/**
 * @brief Executes a built-in command with the given arguments.
 * @param command The built-in command to execute.
 * @param args The arguments for the command.
 */

void execute_builtin(const char* command, char** args)
{
    if (strcmp(command, "cd") == 0)
    {
        if(args[1] == NULL)
        {

            perror("cd expected a argument");
        }
        else if ( chdir(args[1]) != 0)
        {
            perror("cd failed");
        }
    }


    else if (strcmp(command, "exit") == 0)
    {
        exit(0);
    }


    else if (strcmp(command, "help") == 0)
    {
        printf("Built-in commands:\n");
        printf("  cd <directory> - Change the current directory to <directory>\n");
        printf("  exit - Exit the shell\n");
        printf("  help - Display this help message\n");
    }
}