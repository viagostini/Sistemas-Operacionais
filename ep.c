#include "ep.h"

int context = 0;
int finished = 0;

int main(int argc, char* argv[]) {
    int i, close, tam = 0;;
    scheduler = atoi(argv[1]);
    FILE *in = fopen(argv[2], "r");
    out = fopen(argv[3], "w");
    float t0, dt, deadline;
    char name[101];
    Process* v = malloc(sizeof (Process) * 100);

    if (argc != 5 && argc != 4) {
        fprintf(stderr, "Número de parâmetros incorreto.\n");
        return EXIT_FAILURE;
    } else if (argc == 5 && argv[4][0] == 'd')
         debug = TRUE;

    if (in == NULL) {
        fprintf(stderr, "Arquivo nao existe.\n");
        return EXIT_FAILURE;
    }

    while (fscanf(in, "%f %f %f %s", &t0, &dt, &deadline, name) != EOF)
        v[tam++] = create_process(t0, dt, deadline, name);

    if ((close = fclose(in)) != 0)
        fprintf(stderr, "Error closing file!\n");

    printf("SCHEDULER: %d\n", scheduler);
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

    /* Para o debug */
    if (debug)
        fprintf(stderr, "Mudanças de contexto: %d\n", context);

    fprintf(out, "%d", context);
    fclose(out);
    return 0;
}
