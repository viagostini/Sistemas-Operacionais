#include "RR.h"
#include "timer.h"

Node* new_node(Process p) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->process = p;
    tmp->next = NULL;
    return tmp;
}

Queue* new_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->back = NULL;
    return q;
}

void enqueue(Queue* q, Process p) {
    Node* tmp = new_node(p);

    /* Se a lista está vazia, tmp é tanto front quanto back */
    if (q->back == NULL) {
        q->front = q->back = tmp;
        return;
    }

    /* Adiciona o novo node no fim da fila e muda back */
    q->back->next = tmp;
    q->back = tmp;
}

Node* dequeue(Queue* q) {
    /* Se lista está vazia, retorna NULL */
    if (q->front == NULL)
        return NULL;
    /* Guarda front antigo e adianta front para o próximo */
    Node* tmp = q->front;
    q->front = q->front->next;

    /* Se front se tornou NULL, muda back para NULL */
    if (q->front == NULL)
        q->back == NULL;

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
    
    int i;
    float timestamp; /* TO DO: Arrumar um nome melhor */ 
    struct timespec init, now;
    Queue* rr_queue;

    rr_queue = new_queue();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while (i < size) {         /* Ainda tem processos fora da fila de execução */
        clock_gettime(CLOCK_MONOTONIC, &now);
        timestamp = timer_check(now);

        while (v[i]->t0 <= timestamp)        /* Processos chegando */
            enqueue(rr_queue, v[i]);

        Node* next = dequeue(rr_queue);
        Process p = next->process;
        /* Roda este processo por QUANTUM unidades de tempo */
        printf("Rodando processo [%s] por %f segundos\n", p->name, QUANTUM);
        sleep(QUANTUM);
        if (QUANTUM < p->dt) {
            p->dt -= QUANTUM;
            enqueue(rr_queue, p);
        }
    }
}