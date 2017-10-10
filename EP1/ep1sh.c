#include "ep1sh.h"

#define PATH_SIZE 500
#define MAX_ARG_NUM 5

char path[PATH_SIZE];

char *builtin[] = {"chown", "date", "exit"};

int main(int argc, char **argv) {
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
        else
            run_external(input_tokens);
    }

    return 0;
}

/* =======================================
 *
 *              FUNÇÔES
 *
 * ======================================= */

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

void run_external (char **input_tokens) {
    pid_t child_pid;

    if ((child_pid = fork()) == 0) {
        /* Executa o comando no processo filho */
        execve(input_tokens[0], input_tokens, 0);
    } else {
        /* Processo pai espera finalização do processo filho */
        waitpid(child_pid, NULL, 0);
    }
}

void run_builtin (char **input_tokens) {
    int ch;
    time_t  t;
    struct group* newgroup;
    struct tm *now;
    char buffer[80];
    if(strcmp(input_tokens[0], "chown") == 0) {
        newgroup = getgrnam(input_tokens[1]);
        ch = chown(input_tokens[2], -1, newgroup->gr_gid);
    } else if(strcmp(input_tokens[0], "date") == 0) {
        t = time(NULL);
        now = localtime(&t);
        strftime (buffer, 80, "%a %b %d %T %Z %Y\n", now);
        printf("%s", buffer);
    }
}

int is_builtin (char *cmd) {
    int i;
    int cmd_num = sizeof(builtin) / sizeof(builtin[0]);

    for (i = 0; i < cmd_num; i++)
        if (strcmp(cmd, builtin[i]) == 0)
            return 1;
    return 0;
}
