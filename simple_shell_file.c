#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_VALUE_LENGTH 50
#define MAX_NUM_ALIASES 50
#define MAX_INPUT_LENGTH 100

/*
*
* Comments handler
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
    Alias new_alias;
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
    char arg[MAX_INPUT_LENGTH];
    char *equal_sign;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for (i = 0; fgets(arg, MAX_INPUT_LENGTH, fp) != NULL; i++) {
        /* Remove trailing newline */
        arg[strcspn(arg, "\n")] = '\0';

        if (arg[0] == '#') {
            continue;  /* skip comments*/
        }
        equal_sign = strchr(arg, '=');
        if (equal_sign == NULL) {
            print_alias(arg);
        } else {
            *equal_sign = '\0';
            set_alias(arg, equal_sign+1);
        }
    }

    fclose(fp);
    print_aliases();
    return EXIT_SUCCESS;
}

