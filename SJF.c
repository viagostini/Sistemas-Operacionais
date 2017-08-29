#include "SJF.h"

void SJF(Process *v, int size);

void SJF(Process *v, int size) {
    int i = 0;
    float timestamp;
    struct timespec init, now;
    Heap h;

    h = create_heap();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while(h->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp)
            insert_process(h, v[i++]);

        Process p = get_min(h);
        if (p != NULL) {
            printf("Rodando processo [%s] por %f segundos\n", p->name, p->dt);
            run_process(p->dt);
        }
    }
}
