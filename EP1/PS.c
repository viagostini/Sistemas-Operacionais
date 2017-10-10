#include "PS.h"

void PS(Process *v, int size);
float time_ps(float deadline);

void PS(Process *v, int size) {
    int i = 0;
    float timestamp, quantum_time;
    struct timespec init, now;
    Heap h;
    Process prev = NULL;
    pthread_t tid;

    printf("QUANTUM = %f\n", QUANTUM);

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
            quantum_time = time_ps(p->deadline);
            //printf("Rodando processo [%s] por %f segundos\n", p->name, quantum_time >= p->dt ? p->dt : quantum_time);
            if (quantum_time >= p->dt) {
                pthread_create(&tid, NULL, run_process, &p->dt);
                if (debug) {
                    timestamp = timer_check(init);
                    print_debug(CPU_ENTER, p->name, 0, timestamp);
                }
                pthread_join(tid, NULL);
                print_process(p, init);

                timestamp = timer_check(init);
                if (timestamp <= p->deadline + FLT_EPSILON)
                    finished++;

                if (debug) {
                    print_debug(CPU_EXIT, p->name, 0, timestamp);
                    print_debug(PROC_FINISH, p->name, num_out++, timestamp);
                }
            } else {
                if(prev != NULL)
                    context++;
                pthread_create(&tid, NULL, run_process, &quantum_time);
                if (debug) {
                    timestamp = timer_check(init);
                    print_debug(CPU_ENTER, p->name, 0, timestamp);
                }
                pthread_join(tid, NULL);
                if (debug)
                    print_debug(CPU_EXIT, p->name, 0, timestamp);
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
