#ifndef RR_H
#define RR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep() */
#include <time.h>

#include "timer.h" /* timer_check() */
#include "ep.h"
#include "process.h"

/* Variável global QUANTUM criada para definir o quantum padrão dos processos. */
extern const float QUANTUM;

typedef struct node *Node;

struct node {
    Process process;
    Node next;
};

typedef struct queue *Queue;

struct queue {
    int size;
    Node front;
    Node back;
};

/* A função new_node() cria um novo node de lista ligada. */
Node new_node(Process p);

/* A função new_queue() cria uma fila vazia. */
Queue new_queue();

/* A função enqueue() enfileira um processo na fila. */
void enqueue(Queue q, Process p);

/* A função dequeue() remove o primeiro processo da fila. */
Node dequeue(Queue q);

/* A função free_queue() libera memória da fila. */
void free_queue(Queue q);

/* A função show_queue() imprime a fila na saída padrão. */
void show_queue(Queue q);

/* A função RR() executa o algoritmo de escalonamento Round Robin com os
// processos v[0..size-1]. */
void RR(Process *v, int size);

#endif /* RR_H */
