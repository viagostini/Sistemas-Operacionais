#include "ep.h"

int main(int argc, char* argv[]) {
    int simulator = atoi(argv[1]);
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

    switch (simulator) {
        case 1:
            alg = 0;
            SJF(v, tam);
            break;
        case 2:
            alg = 1;
            RR(v, tam);
            break;
        case 3:
            alg = 2;
            PS(v, tam);
            break;
        default:
            fprintf(stderr, "%s\n", "Simulador escolhido nao existe.");
            exit(2);
    }

    return 0;
}
