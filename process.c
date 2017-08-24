#include "process.h"

Process create_process(float t0, float dt, float deadline, char* name);
void swap_process(Process p1, Process p2);
int compare_process(Process p1, Process p2);

int alg;

Process create_process(float t0, float dt, float deadline, char* name) {
    Process new_process = malloc(sizeof (Process*));

    new_process->t0 = t0;
    new_process->dt = dt;
    new_process->deadline = deadline;
    strcpy(new_process->name, name);

    return new_process;
}

void swap_process(Process p1, Process p2) {
    Process p = p1;
    p1 = p2;
    p2 = p;
}

// Precisamos colocar as comparações com epsilon.
int compare_process(Process p1, Process p2) {
    if (alg == 0) {
        if (p1->dt < p2->dt)
            return 1;
        else if (p1->dt > p2->dt)
            return 0;
        else {
            if (p1->deadline <= p2->deadline)
                return 1;
            else
                return 0;
        }
    } else if (alg == 2){
        if (p1->deadline < p2->deadline)
            return 1;
        else if (p1->deadline > p2->deadline)
            return 0;
        else {
            if (p1->dt < p2->dt)
                return 1;
            else
                return 0;
        }
    }
}
