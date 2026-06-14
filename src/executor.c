#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/redirection.h"
#include "../include/pipe.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Executes a command from the token array.
 * @param args NULL-terminated array of tokens.
 */
void execute(char** args)
{
    // check for builtin
    if (is_builtin(args[0]))
    {
        execute_builtin(args[0], args);
        return;
    }

    // check for pipe
    if (has_pipe(args))
    {
        handle_pipe(args);
        return;
    }

    // check for background process
    int background = 0;
    int i = 0;
    while (args[i] != NULL) i++;
    if (i > 0 && strcmp(args[i - 1], "&") == 0)
    {
        background = 1;
        args[i - 1] = NULL;
    }

    // fork + execvp
    pid_t pid = fork();
    if (pid == -1) { perror("fork failed"); return; }

    if (pid == 0)
    {
        // redirection inside child ← key fix
        int j = 0;
        while (args[j] != NULL)
        {
            if (is_redirection(args[j]))
            {
                handle_redirection(args);
                break;
            }
            j++;
        }

        execvp(args[0], args);
        perror("MyShell");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (!background)
            waitpid(pid, NULL, 0);
        else
            printf("[background] pid: %d\n", pid);
    }
}