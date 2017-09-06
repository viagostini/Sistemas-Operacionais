#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h> /* malloc() */
#include "process.h" /* Process, compare_process()*/

extern const int HEAP_SIZE;

/* A estrutura struct heap contém um vetor A[1..size]. // Arrumar essa msg */
struct heap {
    Process *A;
    int size;
    int max_size;
};

typedef struct heap *Heap;

/* A função create_heap() cria um heap. */
Heap create_heap();

/* A função insert_process() insere um processo p no heap h. */
void insert_process(Heap h, Process p);

/* A função get_min() devolve o menor elemento do heap. */
Process get_min(Heap h);

void print_heap(Heap h);

#endif /* HEAP_H */
