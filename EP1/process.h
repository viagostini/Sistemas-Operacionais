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
#include <pthread.h>

#include "timer.h" /* timer_check() */

#define TRUE 1
#define FALSE 0

/* identificadores para o debug */
#define CPU_EXIT 0
#define CPU_ENTER 1
#define PROC_FINISH 2
#define PROC_ARRIVAL 3

/* Estrutura struct process criada para representar um processo. */
struct process {
	float t0, dt, deadline;
    char name[101];
};

/* Process é um ponteiro para struct process. */
typedef struct process *Process;

typedef int boolean;

/* Variável global debug criada para saber se a mensagem de debug deve ser
// impressa. */
extern boolean debug;

/* Variável global num_out criada para saber em que linha de arquivo será
// escrita a saída. */
extern int num_out;

/* Variável alg define o algoritmo que está sendo usado no momento.
// Caso seja o Shortest Job First, marca 1.
// Caso seja o Round Robin, marca 2.
// caso seja o Priority Scheduling, marca 3. */
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

/* A função compare_process() compara o processo p1 com o p2 de acordo com o
// algoritmo que está sendo executado. Devolve 1 caso p1 venha antes que p2 e
// 0 caso contrário. */
int compare_process(Process p1, Process p2);

/* A função run_process() para o programa por time segundos. */
void *run_process(void *time);

/* A função print_process() imprime na tela o processo e o tempo atual em
// relação ao tempo em que se iniciou a execução do programa. */
void print_process(Process p, struct timespec init);

/* A função process_equal() verifica se o processo a é igual ao processo b. */
boolean process_equal(Process a, Process b);

/* A função print_debug() imprime na saída de erro uma mensagem a depender do
// code enviado. */
void print_debug(int code, char *process, int line, float time);

#endif /* PROCESS_H */
