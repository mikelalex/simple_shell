#include <shell.h>
/*
*
*Handle command lines with arguments
*
*/

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_COMMAND_LENGTH];
    int status;
    pid_t pid;
    char *token;
    int i;

    while (1)
    {
        printf(PROMPT);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        command[strcspn(command, "\n")] = '\0';

        i = 0;
        token = strtok(command, " ");

        while (token != NULL) 
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror(args[0]);
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

