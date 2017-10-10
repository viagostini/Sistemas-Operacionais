#ifndef PS_H
#define PS_H

#include <stdio.h> /* printf() */
#include <unistd.h> /* sleep() */

#include "timer.h" /* timer_check() */
#include "heap.h" /* insert_process(), get_min(), create_heap() */
#include "process.h" /* Process */
#include "ep1.h" /* context */

/* A função PS() executa o algoritmo de escalonamento com prioridade com os
// processos v[0..size-1]. */
void PS(Process *v, int size);

/* A função time_ps() calcula o tempo que se deve dar para cada processo. */
float time_ps(float deadline);

#endif /* PS_H */
