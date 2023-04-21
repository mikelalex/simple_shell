#include <shell.h>

/*
*
*Handle commands separator ;
*
*/

int main(int argc, char *argv[], char __attribute__((unused)) *envp[]) {
    char *new_dir;
    char *prev_dir;
    
    new_dir = get_new_dir(argc, argv);
    prev_dir = get_prev_dir();

    if (chdir(new_dir) == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    printf("Previous directory: %s\n", prev_dir);

    update_pwd_env_var();

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

