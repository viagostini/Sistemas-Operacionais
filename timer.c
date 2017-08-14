#include <time.h>

struct timespec timer_start() {
    struct timespec clock;
    
    clock_gettime(CLOCK_MONOTONIC, &clock);
    return clock;
}

float timer_elapsed(struct timespec start, struct timespec end) {
    float f_start = (float) start.tv_sec + (1e-9 * start.tv_nsec);
    float f_end = (float) end.tv_sec + (1e-9 * end.tv_nsec);

    return f_end - f_start;
}

float timer_check(struct timespec timer) {
    struct timespec curr;
    
    clock_gettime(CLOCK_MONOTONIC, &curr);
    return timer_elapsed(curr, timer);
}