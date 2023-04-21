#include "shell.h"

/*
 *
 *variables replacement
 *
 */

 typedef struct {
    char name[MAX_NAME_LENGTH];
    char value[MAX_VALUE_LENGTH];
} Alias;

Alias aliases[MAX_NUM_ALIASES];
int num_aliases = 0;

void print_aliases() {
    int i;
    for (i = 0; i < num_aliases; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void print_alias(char *name) {
    int i;
    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    fprintf(stderr, "alias: %s: not found\n", name);
    exit(EXIT_FAILURE);
}

void set_alias(char *name, char *value) {
    int i;
    Alias new_alias; /* declare new_alias here*/
    if (num_aliases == MAX_NUM_ALIASES) {
        fprintf(stderr, "alias: too many aliases\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < num_aliases; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            strncpy(aliases[i].value, value, MAX_VALUE_LENGTH);
            return;
        }
    }
    strncpy(new_alias.name, name, MAX_NAME_LENGTH);
    strncpy(new_alias.value, value, MAX_VALUE_LENGTH);
    aliases[num_aliases++] = new_alias;
}

int main(int argc, char *argv[]) {
    int i;
    char *arg;
    char *equal_sign;
    if (argc == 1) {
        print_aliases();
    } else {
        for (i = 1; i < argc; i++) {
            arg = argv[i];
            equal_sign = strchr(arg, '=');
            if (equal_sign == NULL) {
                print_alias(arg);
            } else {
                *equal_sign = '\0';
                set_alias(arg, equal_sign+1);
            }
        }
    }
    return EXIT_SUCCESS;
}

