#include "process.h"

Process create_process(float t0, float dt, float deadline, char* name);
void swap_process(Process p1, Process p2);
int compare_process(Process p1, Process p2);
void run_process(float time);
void print_process(Process p, struct timespec init);
boolean process_equal(Process a, Process b);

Scheduler scheduler;

FILE *out;

boolean debug = FALSE;

void print_debug(int code, char *proc_name, int line, float time) {
    int cpu = sched_getcpu();
    fprintf(stderr, "%fs -- ", time);
    switch(code) {
        case CPU_EXIT:
            fprintf(stderr, "Processo [%s] saindo da CPU [%d]\n", proc_name, cpu);
            break;
        case CPU_ENTER:
            fprintf(stderr, "Processo [%s] entrando na CPU [%d]\n", proc_name, cpu);
            break;
        case PROC_FINISH:
            fprintf(stderr, "Processo [%s] finalizado. Escrevendo na linha %d.\n", proc_name, line);
            break;
    }
}

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

int compare_process(Process p1, Process p2) {
    printf("dt do p1: %f\n", p1->dt);
    printf("dt do p2: %f\n", p2->dt);
    if (scheduler == SHORTEST_JOB_FIRST) {
        if (p1->dt < p2->dt - FLT_EPSILON) {
            printf("p1 menor\n");
            return 1;
        } else if (p1->dt > p2->dt + FLT_EPSILON) {
            printf("p2 menor\n");
            return 0;
        } else {
            if (p1->deadline <= p2->deadline - FLT_EPSILON) {
                printf("p1 menor\n");
                return 1;
            } else {
                printf("p2 menor\n");
                return 0;
            }
        }
    } else if (scheduler == PRIORITY) {
        if (p1->deadline < p2->deadline - FLT_EPSILON)
            return 1;
        else if (p1->deadline > p2->deadline + FLT_EPSILON)
            return 0;
        else {
            if (p1->dt < p2->dt - FLT_EPSILON)
                return 1;
            else
                return 0;
        }
    }
}

void run_process(float time) {
    usleep(time * 1000000);
}

void print_process(Process p, struct timespec init) {
    float timestamp = timer_check(init);
    fprintf(out, "%s %f %f\n", p->name, timestamp, timestamp - p->t0);
}

boolean process_equal(Process a, Process b) {
    if (strcmp(a->name, b->name) == 0)
        return TRUE;
    return FALSE;
}
