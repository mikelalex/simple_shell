#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

int main(int __attribute__((unused)) argc,  __attribute__((unused)) char *argv[], char *envp[])
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
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            exit(EXIT_SUCCESS);
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

