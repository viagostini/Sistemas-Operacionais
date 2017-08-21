#include "RR.h"
#include "timer.h"

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
        return;
    }

    /* Adiciona o novo node no fim da fila e muda back */
    q->back->next = tmp;
    q->back = tmp;
    q->size++;
}

Node dequeue(Queue q) {
    /* Se lista está vazia, retorna NULL */
    if (q->front == NULL)
        return NULL;
    /* Guarda front antigo e adianta front para o próximo */
    Node tmp = q->front;
    q->front = q->front->next;

    /* Se front se tornou NULL, muda back para NULL */
    if (q->front == NULL)
        q->back == NULL;

    q->size--;
    return tmp;
}

void RR(Process* v, int size) {
    /*
        1. Enquanto próximo processo tiver início no tempo atual:
        2.      Insere processo na fila
        3. Retira o primeiro processo da fila
        4. Simula este processo por (QUANTUM) unidades de tempo
        5. Se QUANTUM < processo.dt:
        6.      Insere processo na fila com dt = dt - QUANTUM
    */
    
    int i = 0;
    float timestamp; /* TO DO: Arrumar um nome melhor */ 
    struct timespec init, now;
    Queue rr_queue;

    rr_queue = new_queue();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while (rr_queue->size || i < size) {         /* Ainda tem processos fora da fila de execução */
        clock_gettime(CLOCK_MONOTONIC, &now);
        timestamp = timer_check(now);

        while (i < size && v[i]->t0 <= timestamp)       /* Processos chegando */
            enqueue(rr_queue, v[i++]);

        Node next = dequeue(rr_queue);
        if (next != NULL) {
            Process p = next->process;
            
            /* Roda este processo por QUANTUM unidades de tempo */
            printf("Rodando processo [%s] por %f segundos\n", p->name, QUANTUM >= p->dt ? p->dt : QUANTUM);
            if (QUANTUM >= p->dt)
                sleep(p->dt);
            else {
                sleep(QUANTUM);
                p->dt -= QUANTUM;
                enqueue(rr_queue, p);
            }
        }
    }
}
