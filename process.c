#include "process.h"

Process create_process(float t0, float dt, float deadline, char* name);
int compareProcess(Process p1, Process p2);

Process create_process(float t0, float dt, float deadline, char* name) {
    Process new_process = malloc(sizeof (Process*));

    new_process->t0 = t0;
    new_process->dt = dt;
    new_process->deadline = deadline;
    strcpy(new_process->name, name);

    return new_process;
}

int compareProcess(Process p1, Process p2) {
    if (p1->t0 < p2->t0)
        return 1;
    else if (p1->t0 > p2->t0)
        return -1;
    else {
        if (p1->dt < p2->dt)
            return 1;
        else if (p1->dt > p2->dt)
            return -1;
        else {
            if (p1->deadline <= p2->deadline)
                return 1;
            else
                return -1;
        }
    }
}
