#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main (int argc, char* argv[]) {
    int simulator = atoi(argv[1]);
    FILE* f_open = fopen(argv[2], "r");
    float t0, dt, deadline;
    char name[100];
    Process* v = malloc(sizeof (Process) * 100);
    int tam = 0;

    if (f_open == NULL) {
        fprintf(stderr, "%s\n", "Arquivo nao existe.");
        exit(1);
    }

    while (fscanf(f_open, "%f %f %f %s", &t0, &dt, &deadline, name) != EOF) {
        Process p = create_process(t0, dt, deadline, name); // TO DO: criar essa função
        /*printf("%s:\n", p->name);
        printf("t0: %f\n", p->t0);
        printf("dt: %f\n", p->dt);
        printf("deadline: %f\n", p->deadline);
        printf("============================\n");*/
        v[tam++] = p;
    }   

    switch (simulator) {
        case 1:
            //SJF (tam, v);
            break;
        case 2:
            RR (tam, v);
            break;
        case 3:
            //PS (tam, v);
            break;
        default:
            fprintf(stderr, "%s\n", "Simulador escolhido nao existe.");
            exit(2);
    }

    return 0;

}



