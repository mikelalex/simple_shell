#include <shell.h>

/*
*
*Handle the && and || shell logical operators
*
*/

int main(int argc, char *argv[], char __attribute__((unused)) *envp[]) {
    int i = 1;
    char *new_dir;
    char *prev_dir;

    while (i < argc) {
        /* Get the next command and check for && and || operators */
        new_dir = get_new_dir(argc - i, argv + i);
        if (strcmp(new_dir, "&&") == 0) {
            /* Command succeeded, continue to the next one */
            i += 2;
            continue;
        } else if (strcmp(new_dir, "||") == 0) {
            /* Command failed, skip to the next one */
            i += 2;
            if (i >= argc) {
                /* No more commands to execute */
                break;
            }
            new_dir = get_new_dir(argc - i, argv + i);
            if (strcmp(new_dir, "&&") == 0) {
                /* Skip the failed command and continue to the next one */
                i += 2;
                continue;
            }
        }

        /* Execute the current command */
        prev_dir = get_prev_dir();
        if (chdir(new_dir) == -1) {
            perror("chdir");
            exit(EXIT_FAILURE);
        }
        printf("Previous directory: %s\n", prev_dir);
        update_pwd_env_var();

        i++;
    }

    return EXIT_SUCCESS;
}

char *get_home_dir() {
    char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        fprintf(stderr, "cd: HOME environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return home_dir;
}

char *get_prev_dir() {
    char *prev_dir = getenv("PWD");
    if (prev_dir == NULL) {
        fprintf(stderr, "cd: previous directory not set\n");
        exit(EXIT_FAILURE);
    }
    return prev_dir;
}

char *get_new_dir(int argc, char *argv[]) {
    char *new_dir = NULL;
    if (argc == 1) {
        new_dir = get_home_dir();
    } else if (strcmp(argv[1], "-") == 0) {
        new_dir = get_prev_dir();
    } else {
        new_dir = argv[1];
    }

    if (new_dir == NULL) {
        fprintf(stderr, "cd: could not determine new directory\n");
        exit(EXIT_FAILURE);
    }

    return new_dir;
}

void update_pwd_env_var() {
    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, MAX_PATH_LENGTH) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    if (setenv("PWD", cwd, 1) == -1) {
        perror("setenv");
        exit(EXIT_FAILURE);
    }
}

