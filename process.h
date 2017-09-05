#ifndef PROCESS_H
#define PROCESS_H
#define _GNU_SOURCE

#include <string.h> /* strcpy() */
#include <stdlib.h> /* malloc()*/
#include <stdio.h> /* FILE */
#include <float.h> /* FLT_EPSILON = 1E-5 */
#include <time.h> /* clock_gettime(), CLOCK_MONOTONIC */
#include <unistd.h> /* usleep() */
#include <sched.h> /* sched_getcpu() */

#include "timer.h" /* timer_check() */



#define TRUE 1
#define FALSE 0

/* identificadores para o debug */
#define CPU_EXIT 0
#define CPU_ENTER 1

#define PROC_FINISH 0
#define PROC_ARRIVAL 1

/* Estrutura struct process criada para representar um processo. */
struct process {
	float t0, dt, deadline;
    char name[101];
};

/* Process é um ponteiro para struct process. */
typedef struct process *Process;

typedef int boolean;

extern boolean debug;

/* Variável alg define o algoritmo que está sendo usado no momento.
// Caso seja o Shortest Job First, marca 0.
// Caso seja o Round Robin, marca 1.
// caso seja o Priority Scheduling, marca 2. */
enum scheduler_choice {
	SHORTEST_JOB_FIRST = 1,
	ROUND_ROBIN,
	PRIORITY
};

typedef enum scheduler_choice Scheduler;

extern Scheduler scheduler;

extern FILE *out;

/* A função create_process() cria um processo. Sendo t0 o tempo de chegada do
// processo, dt o tempo que ele é executado, deadline o tempo máximo que ele
// pode executar e name o nome do processo. */
Process create_process(float t0, float dt, float deadline, char* name);

/* A função swap_process() troca o processo p1 pelo p2 e vice versa. */
void swap_process(Process p1, Process p2);

/* A função compare_process() compara o processo p1 com o p2 de acordo com o
// algoritmo que está sendo executado. Devolve 1 caso p1 venha antes que p2 e
// 0 caso contrário. */
int compare_process(Process p1, Process p2);

/* A função run_process() para o programa por time segundos. */
void run_process(float time);

void print_process(Process p, struct timespec init);

boolean process_equal(Process a, Process b);

void print_debug(int code, char *process, int line, float time);

#endif /* PROCESS_H */
