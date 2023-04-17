#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *envp[])
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
        token = command;

        while (*token != '\0')
        {
            while (*token == ' ')
            {
                token++;
            }

            if (*token == '\0')
            {
                break;
            }

            args[i++] = token;

            while (*token != ' ' && *token != '\0')
            {
                token++;
            }

            if (*token == '\0')
            {
                break;
            }

            *token = '\0';
            token++;
        }

        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            if (args[1] != NULL)
            {
                int exit_status = atoi(args[1]);
                exit(exit_status);
            }
            else
            {
                exit(EXIT_SUCCESS);
            }
        }
        else if (strcmp(args[0], "env") == 0)
        {
            char **env;
            for (env = envp; *env != 0; env++)
            {
                printf("%s\n", *env);
            }
        }
        else
        {
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
    }

    return 0;
}

