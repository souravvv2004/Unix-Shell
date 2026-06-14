#include "../include/redirection.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Checks if a single token is a redirection operator.
 * @param token The token to check.
 * @return 1 if redirection operator, 0 otherwise.
 */
int is_redirection(const char* token)
{
    return (strcmp(token, ">")  == 0 ||
            strcmp(token, ">>") == 0 ||
            strcmp(token, "<")  == 0);
}

/**
 * @brief Handles redirection by opening file and calling dup2.
 * @param tokens The token array to process.
 * @return 1 if handled successfully, 0 otherwise.
 */
int handle_redirection(char** tokens)
{
    int i = 0;
    int fd;
    int redirect_type = 0; // 1 = output, 2 = append, 3 = input

    while (tokens[i] != NULL)
    {
        if      (strcmp(tokens[i], ">")  == 0) { redirect_type = 1; break; }
        else if (strcmp(tokens[i], ">>") == 0) { redirect_type = 2; break; }
        else if (strcmp(tokens[i], "<")  == 0) { redirect_type = 3; break; }
        i++;
    }

    if (redirect_type == 0 || tokens[i + 1] == NULL)
    {
        fprintf(stderr, "Error: Invalid redirection syntax.\n");
        return 0;
    }

    const char* filename = tokens[i + 1];

    switch (redirect_type)
    {
        case 1: fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,  0644); break;
        case 2: fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644); break;
        case 3: fd = open(filename, O_RDONLY);                             break;
        default: return 0;
    }

    if (fd < 0)
    {
        perror("Error opening file");
        return 0;
    }

    if (redirect_type == 3)
    {
        if (dup2(fd, STDIN_FILENO) < 0)  { perror("dup2 failed"); close(fd); return 0; }
    }
    else
    {
        if (dup2(fd, STDOUT_FILENO) < 0) { perror("dup2 failed"); close(fd); return 0; }
    }

    close(fd);

    tokens[i]     = NULL;  // remove operator
    tokens[i + 1] = NULL;  // remove filename

    return 1;
}