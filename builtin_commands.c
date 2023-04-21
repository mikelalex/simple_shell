#include <shell.h>
/*
*
*setenv and unsetenv builtin commands
*
*/

void set_env_variable(char *var_name, char *var_value) {
    int overwrite = 1;
    if (setenv(var_name, var_value, overwrite) != 0) {
        fprintf(stderr, "Failed to set environment variable %s\n", var_name);
    }
}

void unset_env_variable(char *var_name) {
    if (unsetenv(var_name) != 0) {
        fprintf(stderr, "Failed to unset environment variable %s\n", var_name);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Usage: %s setenv VARIABLE VALUE\n       %s unsetenv VARIABLE\n", argv[0], argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "setenv") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s setenv VARIABLE VALUE\n", argv[0]);
            return 1;
        }
        set_env_variable(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "unsetenv") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s unsetenv VARIABLE\n", argv[0]);
            return 1;
        }
        unset_env_variable(argv[2]);
    }
    else {
        fprintf(stderr, "Invalid command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

