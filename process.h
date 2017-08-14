#ifndef PROCESS_H
#define PROCESS_H

struct process {
    char name[100];
    float t0;
    float dt;
    float deadline;
};

typedef struct process *Process;

Process create_process(float t0, float dt, float deadline) {
    Process* new_process = malloc(sizeof Process);
    
    new_process.t0 = t0;
    new_process.dt = dt;
    new_process.deadline = deadline;

    return new_process;
}

#endif /* PROCESS_H */
