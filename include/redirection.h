#ifndef REDIRECTION_H
#define REDIRECTION_H

/** 
 *  @brief Checks if a command is a redirection command.
 *  @param command The token array to check.
 *  @return 1 if the command is a redirection command, 0 otherwise.
 */
int is_redirection(const char* tokens);


/**
 *  @brief Handle the redirection command 
 *  @param tokens The The token array to execute.
 *  @return 1  if redirection handle successfully , 0 otherwise
 */
int handle_redirection(char** tokens);

#endif
