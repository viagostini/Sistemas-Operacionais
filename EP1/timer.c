#include "timer.h"

float timer_check(struct timespec init);
static float timer_elapsed(struct timespec start, struct timespec end);

/* A função timer_elapsed() devolve um float que representa o tempo que passou
// entre dois instantes de tempo, representados por timespecs, em segundos. */
static float timer_elapsed(struct timespec start, struct timespec end) {
    float f_start = (float) start.tv_sec + (1e-9 * start.tv_nsec);
    float f_end = (float) end.tv_sec + (1e-9 * end.tv_nsec);

    return f_end - f_start;
}

float timer_check(struct timespec init) {
    struct timespec curr;

    clock_gettime(CLOCK_MONOTONIC, &curr);
    return timer_elapsed(init, curr);
}
