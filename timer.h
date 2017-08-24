#ifndef TIMER_H
#define TIMER_H

#include <time.h>

float timer_elapsed(struct timespec start, struct timespec end);
float timer_check(struct timespec init);

#endif /* TIMER_H */
