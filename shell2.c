#include <shell.h>

/*
*
*Handle the PATH
*fork must not be called if the command doesn’t exist
*
*/

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_COMMAND_LENGTH];
    char command_path[MAX_COMMAND_LENGTH];
    char *path;
    char *token;
    int status;
    pid_t pid;
    int found;
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

        /* Check if the command exists */
        found = 0;
        path = getenv("PATH");
        token = strtok(path, ":");
        while (token != NULL)
        {
            sprintf(command_path, "%s/%s", token, args[0]);
            if (access(command_path, F_OK) == 0)
            {
                found = 1;
                break;
            }
            token = strtok(NULL, ":");
        }

        if (!found)
        {
            printf("%s: command not found\n", args[0]);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execv(command_path, args) == -1)
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

