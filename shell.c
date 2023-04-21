#include <shell.h>

/*
*Usage: simple_shell
*
*
*Display a prompt and wait for the user to type a command
*/

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[] = {NULL};
    int status;
    pid_t pid;

    while (1)
    {
        printf(PROMPT);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execvp(command, args) == -1)
            {
                perror(command);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (wait(&status) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}

