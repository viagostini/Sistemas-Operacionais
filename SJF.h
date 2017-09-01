#ifndef SJF_H
#define SJF_H

#include <stdio.h> /* printf() */
#include <unistd.h> /* sleep() */
#include <time.h> /* clock_gettime(), CLOCK_MONOTONIC */

#include "timer.h" /* timer_check() */
#include "heap.h" /* insert_process(), get_min(), create_heap() */
#include "process.h" /* Process */
#include "ep.h"

/* A função SJF() executa o algoritmo de escalonamento Shortest Job First com os
// processos v[0..size-1]. */
void SJF(Process *v, int size);

#endif
