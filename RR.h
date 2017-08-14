#ifndef RR_H
#define RR_H

#define QUANTUM 2

struct node {
    Process process;
    Node *next;
} Node;

struct queue {
    Node *front;
    Node *back;
} Queue;

/* Cria um novo node de lista ligada*/
Node* new_node(Process p);

/* Cria uma fila vazia */
Queue* new_queue();

/* Enfileira um processo na fila */
void enqueue(Queue* q, Process p);

/* Remove o primeiro processo da fila */
Node* dequeue(Queue* q);

/* Libera memória da fila */
void free_queue(Queue* q);



void RR(Process* v, int size);

#endif /* RR_H */
