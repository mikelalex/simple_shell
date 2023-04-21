#include "shell.h"

/*
*
*Write your own getline function
*Use a buffer to read many chars at once and call the least possible the read system call
*You will need to use static variables
*You are not allowed to use getline
*
*/

char* my_getline() {
    static char buffer[BUFFER_SIZE];
    static int pos = 0;
    static ssize_t len = 0;
    char* line = NULL;
    int line_len = 0;
    int c;

    while (1) {
        if (pos >= len) {
            len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (len <= 0) {
                break;
            }
            pos = 0;
        }

        c = buffer[pos++];
        if (c == '\n' || c == EOF) {
            break;
        }

        if (line_len % BUFFER_SIZE == 0) {
            line = realloc(line, line_len + BUFFER_SIZE);
            if (!line) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        line[line_len++] = c;
    }

    if (line_len == 0 && len <= 0) {
        return NULL;
    }

    if (line_len % BUFFER_SIZE == 0) {
        line = realloc(line, line_len + 1);
        if (!line) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    line[line_len] = '\0';

    return line;
}

int main() {
    char* line;

    while (1) {
        printf("> ");
        fflush(stdout);

        line = my_getline();
        if (line == NULL) {
            printf("Goodbye!\n");
            break;
        }

        printf("You typed: %s\n", line);
        free(line);
    }

    return 0;
}

