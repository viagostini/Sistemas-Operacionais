#ifndef RR_H
#define RR_H

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include <unistd.h> /* sleep() */

#define QUANTUM 2.0 // Deu erro de multipla definição de variavel
// const float QUANTUM = 2;

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

/* Cria um novo node de lista ligada*/
Node new_node(Process p);

/* Cria uma fila vazia */
Queue new_queue();

/* Enfileira um processo na fila */
void enqueue(Queue q, Process p);

/* Remove o primeiro processo da fila */
Node dequeue(Queue q);

/* Libera memória da fila */
void free_queue(Queue q);


void RR(Process* v, int size);

#endif /* RR_H */
