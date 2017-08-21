#include "process.h"

Process create_process(float t0, float dt, float deadline, char* name) {
    Process new_process = malloc(sizeof new_process);
    
    new_process->t0 = t0;
    new_process->dt = dt;
    new_process->deadline = deadline;
    strcpy(new_process->name, name);

    return new_process;
}