#include <stdio.h>
#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Parses a string into an array of tokens.
 * @param input The input string to be parsed.
 * @return A NULL-terminated array of token strings.
 */
char** parse_input(char* input)
{
    char** tokens = malloc(MAX_TOKENS * sizeof(char*));
    if (tokens == NULL) {
        perror("malloc failed");
        return NULL;
    }

    int token_count = 0;
    char* p = input;

    while (*p)
    {
        while (*p == ' ' || *p == '\t' || *p == '\n')
            p++;

        if (*p == '\0')
            break;

        tokens[token_count++] = p;

        while (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
            p++;

        if (*p) {
            *p = '\0';
            p++;
        }
    }

    tokens[token_count] = NULL;
    return tokens;
}




/**
 * @brief Frees the token array returned by parse_input.
 * @param tokens NULL-terminated array of tokens to free.
 */
void free_tokens(char** tokens)
{
    free(tokens);
}