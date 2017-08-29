#include "ep.h"

int main(int argc, char* argv[]) {
    int i, close;
    scheduler = atoi(argv[1]);
    FILE* f_open = fopen(argv[2], "r");
    int tam = 0;
    float t0, dt, deadline;
    char name[101];
    Process* v = malloc(sizeof (Process) * 100);

    if (f_open == NULL) {
        fprintf(stderr, "%s\n", "Arquivo nao existe.");
        exit(1);
    }

    while (fscanf(f_open, "%f %f %f %s", &t0, &dt, &deadline, name) != EOF) {
        v[tam++] = create_process(t0, dt, deadline, name);
        if (DEBUG) {
            printf("%s:\n", v[tam-1]->name);
            printf("t0: %f\n", v[tam-1]->t0);
            printf("dt: %f\n", v[tam-1]->dt);
            printf("deadline: %f\n", v[tam-1]->deadline);
            printf("============================\n");
        }
    }

    if ((close = fclose(f_open)) != 0)
        fprintf(stderr, "Error closing file!\n");

    switch (scheduler) {
        case 0:
            SJF(v, tam);
            break;
        case 1:
            RR(v, tam);
            break;
        case 2:
            PS(v, tam);
            break;
        default:
            fprintf(stderr, "%s\n", "Simulador escolhido nao existe.");
            exit(2);
    }

    for (i = 0; i < tam; i++) {
        free(v[i]->name);
        free(v[i]);
    }
    free(v);

    return 0;
}
