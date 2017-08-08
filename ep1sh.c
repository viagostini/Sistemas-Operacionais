#include "ep1sh.h"

#define PATH_SIZE 500
#define MAX_ARG_NUM 5

char path[PATH_SIZE];

char *builtin[] = {"chown", "date", "exit"};

int main (int argc, char **argv) {
    char prompt[PATH_SIZE+4];
    char *input, **input_tokens;

    getcwd(path, sizeof(path));
    using_history();

    while (1) {
        sprintf(prompt, "[%s]$ ", path);
        input = readline(prompt);
        add_history(input);
        input_tokens = tokenize(input);
        free(input);
        if (is_builtin(input_tokens[0]))
            run_builtin(input_tokens);
    }

    return 0;
}

/* 
 * =======================================
 *
 *              FUNÇÔES
 *
 * =======================================
 */

char **tokenize (char *str) {
    int i = 0;
    char *token, **args;

    token = strtok(str, " ");
    args = (char**)malloc(MAX_ARG_NUM * sizeof(char*) + 1);

    while (token != NULL) {
        int len = strlen(token);
        args[i] = (char *)malloc(len * sizeof(char));
        strcpy(args[i], token);
        token = strtok(NULL, " ");
        i++;
    }

    args[i] = NULL;
    return args;
}

void run_builtin (char **input_tokens) {
    int ch;
    struct group* newgroup;
    if(strcmp(input_tokens[0], "chown") == 0) {
        newgroup = getgrnam(input_tokens[1]);
        ch = chown(input_tokens[2], -1, newgroup->gr_gid);
    }

    if(strcmp(input_tokens[0], "exit") == 0)
        exit(EXIT_SUCCESS);
}

int is_builtin (char *cmd) {
    int i;
    int cmd_num = sizeof(builtin) / sizeof(builtin[0]);
    
    for (i = 0; i < cmd_num; i++)
        if (strcmp(cmd, builtin[i]) == 0)
            return 1;
    return 0;
}
