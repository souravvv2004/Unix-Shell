#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h> 
#include <readline/history.h>   


/**
 * @brief Entry point of the shell.
 * @return 0 on clean exit.
 */


int main()
{
    

    char* line;
    setup_signals();

    while (1)
    {
        //write(stdout , "MyShell > ",11);
        line = readline("C_Shell > ");
	
	
        if (line == NULL)
        {
            printf("\nBye!\n");
            break;
        }


        else
        {
    
            add_history(line);         
        }

        char** tokens = parse_input(line);

        if (tokens == NULL || tokens[0] == NULL)
        {
            free_tokens(tokens);
            continue;
        }

        execute(tokens);
        free_tokens(tokens);
    }

    return 0;
}
