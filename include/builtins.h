#ifndef BUILTINS_H
#define BUILTINS_H



/**
 * @brief This function checks if the given command is a built-in command.
 * @param command The command string to check.
 * @return 1 if the command is a built-in command, 0 otherwise.
 */


int is_builtin(const char* command);



/**
 * @brief Executes a built-in command with the given arguments.
 * @param command The built-in command to execute.
 * @param args The arguments for the command.
 */
void execute_builtin(const char* command, char** args);

#endif 