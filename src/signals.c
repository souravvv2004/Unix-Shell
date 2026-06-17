
#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include "../include/signals.h"
#include <unistd.h>
#include <sys/wait.h>

/**
 * @brief Handles SIGINT signal (Ctrl+C).
 * @param sig Signal number.
 */
void sigint_handler(int sig)
{
	(void) sig;
    write(STDOUT_FILENO, "\nC_Shell > ", 11);
}

/**
 * @brief Handles SIGCHLD to prevent zombie processes.
 * @param sig Signal number.
 */
void sigchld_handler(int sig)
{
    (void) sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

/**
 * @brief Sets up signal handlers for the shell.
 */
void setup_signals(void)
{   
    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    struct sigaction sa_chld;
    sa_chld.sa_handler = sigchld_handler;
    sigemptyset(&sa_chld.sa_mask);
    sa_chld.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa_chld, NULL);
}
