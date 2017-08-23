#ifndef PROCESS_H
#define PROCESS_H

#include <string.h>
#include <stdlib.h>

struct process {
	float t0, dt, deadline;
    char name[101];
};

typedef struct process *Process;

Process create_process(float t0, float dt, float deadline, char* name);

#endif /* PROCESS_H */
