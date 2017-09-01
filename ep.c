#include "ep.h"

int context = 0;

int main(int argc, char* argv[]) {
    int i, close;
    scheduler = atoi(argv[1]);
    FILE *in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
    int tam = 0;
    float t0, dt, deadline;
    char name[101];
    Process* v = malloc(sizeof (Process) * 100);

    if (argc != 4) {
        fprintf(stderr, "Número de parâmetros incorreto.\n");
        return EXIT_FAILURE;
    }
    if (in == NULL) {
        fprintf(stderr, "Arquivo nao existe.\n");
        return EXIT_FAILURE;
    }

    while (fscanf(in, "%f %f %f %s", &t0, &dt, &deadline, name) != EOF) {
        v[tam++] = create_process(t0, dt, deadline, name);
        if (DEBUG) {
            printf("%s:\n", v[tam-1]->name);
            printf("t0: %f\n", v[tam-1]->t0);
            printf("dt: %f\n", v[tam-1]->dt);
            printf("deadline: %f\n", v[tam-1]->deadline);
            printf("============================\n");
        }
    }

    if ((close = fclose(in)) != 0)
        fprintf(stderr, "Error closing file!\n");

    switch (scheduler) {
        case 1:
            SJF(v, tam);
            break;
        case 2:
            RR(v, tam);
            break;
        case 3:
            PS(v, tam);
            break;
        default:
            fprintf(stderr, "Simulador escolhido nao existe.\n");
            exit(2);
    }

    for (i = 0; i < tam; i++)
        free(v[i]);
    free(v);

    fprintf(out, "%d\n", context);
    fclose(out);
    return 0;
}
