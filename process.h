#ifndef PROCESS_H
#define PROCESS_H

#include <string.h>
#include <stdlib.h>

struct process {
    char name[100];
    float t0;
    float dt;
    float deadline;
};

typedef struct process *Process;

Process create_process(float t0, float dt, float deadline, char* name);

#endif /* PROCESS_H */
