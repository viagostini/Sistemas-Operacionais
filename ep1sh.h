#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * A função tokenize() recebe uma string str e a particiona em uma
 * array de strings args.
 */

char **tokenize (char *str);

/*
 * A função run_builtin() recebe a array de strings input_tokens e
 * decide qual comando embutido deve ser rodado pelo shell.
 */

void run_builtin (char **input_tokens);

/*
 * A função run_external() recebe a array de strings input_tokens e
 * decide qual comando embutido deve ser rodado pelo shell.
 */

void run_external (char **input_tokens);

/*
 * A função is_builtin() recebe a string cmd e retorna true caso
 * a string identifique um comando embutido e false caso contrário.
 */

int is_builtin (char *cmd);

#endif  /* SHELL_H_ */
