#include "SJF.h"

void SJF(Process *v, int size);

void SJF(Process *v, int size) {
    int i = 0;
    float timestamp;
    struct timespec init, now;
    Heap h;
    Process prev = NULL;
    pthread_t tid;

    h = create_heap();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while(h->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp) {
            if (debug)
                print_debug(PROC_ARRIVAL, v[i]->name, i + 1, timestamp);
            insert_process(h, v[i++]);
        }

        Process p = get_min(h);

        if (p != NULL) {
            //printf("Rodando processo [%s] por %f segundos\n", p->name, p->dt);
            pthread_create(&tid, NULL, run_process, &p->dt);
            if (debug) {
                timestamp = timer_check(init);
                print_debug(CPU_ENTER, p->name, 0, timestamp);
            }
            pthread_join(tid, NULL);

            timestamp = timer_check(init);
            if (debug) {
                print_debug(CPU_EXIT, p->name, 0, timestamp);
                print_debug(PROC_FINISH, p->name, num_out++, timestamp);
            }
            if (timestamp <= p->deadline + FLT_EPSILON)
                finished++;

            print_process(p, init);
        }
        prev = p;
    }
}
