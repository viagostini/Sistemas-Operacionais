#include "SJF.h"

void SJF(Process *v, int size);

void SJF(Process *v, int size) {
    int i = 0;
    float timestamp;
    struct timespec init, now;
    Heap h;
    Process prev = NULL;

    h = create_heap();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while(h->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp) {
            printf("%s INSERIDO\n", v[i]->name);
            insert_process(h, v[i++]);
        }

        Process p = get_min(h);
        printf("%s PEGO\n", p->name);

        if(prev != NULL && !process_equal(p, prev))
            context++;
        if (p != NULL) {
            printf("Rodando processo [%s] por %f segundos\n", p->name, p->dt);
            run_process(p->dt);
            print_process(p, init);
        }
        prev = p;
    }
}
