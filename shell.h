#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/*for UNIX command line interpreter*/
#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

/* for getline */
#define BUFFER_SIZE 1024

/*for no strtok allowed */
#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

/*handle arguments for the built-in exit*/
#define MAX_COMMAND_LENGTH 1024
#define PROMPT "> "

/*setenv and unsetenv builtin commands*/
#define MAX_ARGS 3
#define MAX_ENV_VAR_LENGTH 256
#define MAX_ENV_VALUE_LENGTH 256

extern char **environ;

/* to Implement the builtin command cd: */
#define MAX_PATH_LENGTH 1024

void update_pwd_env_var();
char *get_home_dir();
char *get_prev_dir();
char *get_new_dir(int argc, char *argv[]);

/* for Handle commands separator ; */
#define MAX_PATH_LENGTH 1024

void update_pwd_env_var();
char *get_home_dir();
char *get_prev_dir();
char *get_new_dir(int argc, char *argv[]);

/*for Handle the && and || shell logical operators*/
#define MAX_PATH_LENGTH 1024

void update_pwd_env_var();
char *get_home_dir();
char *get_prev_dir();
char *get_new_dir(int argc, char *argv[]);

/* for alias builtin command */
#define MAX_ALIAS_LENGTH 1024
#define MAX_NAME_LENGTH 1024
#define MAX_VALUE_LENGTH 1024
#define MAX_NUM_ALIASES 1024

/* for variable replacement */
#define MAX_ALIAS_LENGTH 1024
#define MAX_NAME_LENGTH 1024
#define MAX_VALUE_LENGTH 1024
#define MAX_NUM_ALIASES 1024

/* for comments handler */
#define MAX_ALIAS_LENGTH 1024
#define MAX_NAME_LENGTH 1024
#define MAX_VALUE_LENGTH 1024
#define MAX_NUM_ALIASES 1024
#define MAX_INPUT_LENGTH 1024

#define MAX_NAME_LENGTH 50
#define MAX_VALUE_LENGTH 50
#define MAX_NUM_ALIASES 100
#define MAX_INPUT_LENGTH 100


#endif
