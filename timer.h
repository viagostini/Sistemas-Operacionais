#ifndef TIMER_H
#define TIMER_H

#include <time.h>

/* A função timer_elapsed() devolve um float que representa o tempo que passou
   entre dois instantes de tempo, representados por timespecs, em segundos. */
float timer_elapsed(struct timespec start, struct timespec end);

/* A função timer_check() devolve um float que representa o tempo que passou em
   relação à um instante de tempo inicial init */
float timer_check(struct timespec init);

#endif /* TIMER_H */
