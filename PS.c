#include "PS.h"

void PS(Process *v, int size);
float time_ps(float deadline);

void PS(Process *v, int size) {
    int i = 0;
    float timestamp, quantum_time;
    struct timespec init, now;
    Heap h;
    Process prev = NULL;

    h = create_heap();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while(h->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp)
            insert_process(h, v[i++]);

        Process p = get_min(h);

        if(prev != NULL)
            context++;
        if (p != NULL) {
            quantum_time = time_ps(p->deadline);
            printf("Rodando processo [%s] por %f segundos\n", p->name, quantum_time >= p->dt ? p->dt : quantum_time);
            if (quantum_time >= p->dt) {
                run_process(p->dt);
                print_process(p, init);
            } else {
                run_process(quantum_time);
                p->dt -= quantum_time;

                timestamp = timer_check(init);

                while (i < size && v[i]->t0 <= timestamp)
                    insert_process(h, v[i++]);

                insert_process(h, p);
            }
        }
        prev = p;
    }
}

float time_ps(float deadline) {
   return (1.0 / deadline) * QUANTUM;
}
