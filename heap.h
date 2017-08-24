#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include "process.h"

#define HEAP_SIZE 101 // Deu erro de multipla definição de variavel
// const int HEAP_SIZE = 101; // Pode alterar nome.

/* A estrutura struct heap contém um vetor A[1..size]. // Arrumar essa msg */
struct heap {
    Process *A;
    int size;
    int max_size;
};

typedef struct heap *Heap;

Heap create_heap();
void insert_process(Heap h, Process p);
void constroi_min_heap(Heap h);
Process get_min(Heap h);

#endif /* HEAP_H */
