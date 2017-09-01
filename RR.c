#include "RR.h"

Node new_node(Process p);
Queue new_queue();
void enqueue(Queue q, Process p);
Node dequeue(Queue q);
void show_queue(Queue q);
void RR(Process* v, int size);

const float QUANTUM = 1.2;

Node new_node(Process p) {
    Node tmp = malloc(sizeof(Node*));
    tmp->process = p;
    tmp->next = NULL;
    return tmp;
}

Queue new_queue() {
    Queue q = malloc(sizeof(Queue*));
    q->size = 0;
    q->front = q->back = NULL;
    return q;
}

void enqueue(Queue q, Process p) {
    Node tmp = new_node(p);

    /* Se a lista está vazia, tmp é tanto front quanto back */
    if (q->back == NULL) {
        q->front = q->back = tmp;
    } else { /* Adiciona o novo node no fim da fila e muda back */
        q->back->next = tmp;
        q->back = tmp;
    }

    q->size++;
}

Node dequeue(Queue q) {
    /* Se lista está vazia, retorna NULL */
    if (q->front == NULL)
        return NULL;
    /* Guarda front antigo e adianta front para o próximo */
    Node tmp = q->front;
    q->front = q->front->next;
    q->size--;

    /* Se front se tornou NULL, muda back para NULL */
    if (q->size == 0)
        q->back = q->front = NULL;

    return tmp;
}

void show_queue(Queue q) {
    Node tmp;
    for (tmp = q->front; tmp != NULL; tmp = tmp->next) {
        Process p = tmp->process;
        printf("%s:\n", p->name);
        printf("t0: %f\n", p->t0);
        printf("dt: %f\n", p->dt);
        printf("deadline: %f\n", p->deadline);
        printf("============================\n");
        printf("oi\n");
    }
}

void free_queue(Queue q) {
    Node tmp;

    while (q->size != 0) {
        tmp = dequeue(q);
        free(tmp);
    }

    free(q);
}

/*
    1. Enquanto próximo processo tiver início no tempo atual:
    2.      Insere processo na fila
    3. Retira o primeiro processo da fila
    4. Simula este processo por (QUANTUM) unidades de tempo
    5. Se QUANTUM < processo.dt:
    6.      Insere processo na fila com dt = dt - QUANTUM
*/
void RR(Process* v, int size) {
    if (DEBUG)
        printf("======= Round Robin ========\n============================\n");


    if (DEBUG_RR) {
        int j;
        for (j = 0; j < size; j++) {
            printf("%s:\n", v[j]->name);
            printf("t0: %f\n", v[j]->t0);
            printf("dt: %f\n", v[j]->dt);
            printf("deadline: %f\n", v[j]->deadline);
            printf("============================\n");
        }
    }

    int i = 0;
    context = 0;
    float timestamp;
    struct timespec init, now;
    Queue rr_queue;
    Process prev = NULL;

    rr_queue = new_queue();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while (rr_queue->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp)
            enqueue(rr_queue, v[i++]);

        if (DEBUG_RR)
            show_queue(rr_queue);
        Node next = dequeue(rr_queue);

        if (next != NULL) {
            Process p = next->process;
            if(prev != NULL && !process_equal(p, prev))
                context++;

            printf("Rodando processo [%s] por %f segundos\n", p->name, QUANTUM >= p->dt ? p->dt : QUANTUM);
            if (QUANTUM >= p->dt) {
                run_process(p->dt);
                print_process(p, init);
            } else {
                run_process(QUANTUM);
                p->dt -= QUANTUM;
                enqueue(rr_queue, p);
            }
            prev = p;
        }
    }
    free_queue(rr_queue);
}
