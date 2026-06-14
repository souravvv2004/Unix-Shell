#include "../include/pipe.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define EXIT_FAILURE 1
/**
 * @brief Checks if a pipe operator exists in token array.
 * @param tokens The token array to check.
 * @return 1 if pipe found, 0 otherwise.
 */
int has_pipe(char** tokens)
{
    int i = 0;
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "|") == 0) return 1;
        i++;
    }
    return 0;
}

/**
 * @brief Handles piping between two commands.
 * @param tokens The token array containing both commands and pipe operator.
 */
void handle_pipe(char** tokens)
{
    // find pipe position
    int pipe_pos = 0;
    while (tokens[pipe_pos] != NULL && strcmp(tokens[pipe_pos], "|") != 0)
        pipe_pos++;

    tokens[pipe_pos] = NULL;               // split into two commands
    char** right = tokens + pipe_pos + 1;  // right side command

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t cpid1 = fork();
    if (cpid1 == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (cpid1 == 0)  // first child — left command
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) { perror("dup2"); exit(EXIT_FAILURE); }
        close(pipefd[1]);
        execvp(tokens[0], tokens);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid_t cpid2 = fork();
    if (cpid2 == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (cpid2 == 0)  // second child — right command
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) < 0) { perror("dup2"); exit(EXIT_FAILURE); }
        close(pipefd[0]);
        execvp(right[0], right);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // parent
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(cpid1, NULL, 0);
    waitpid(cpid2, NULL, 0);
}