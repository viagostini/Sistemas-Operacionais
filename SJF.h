#ifndef SJF_H
#define SJF_H

#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <unistd.h>
#include "ep.h"

#define HEAP_SIZE 101 // Deu erro de multipla definição de variavel
// const int HEAP_SIZE = 101; // Pode alterar nome.

/* A estrutura struct heap contém um vetor A[1..size]. // Arrumar essa msg */
struct heap {
    Process *A;
    int size;
    int max_size;
};

typedef struct heap *Heap;

int parent(int i);
int left_child(int i);
int right_child(int i);
Heap create_heap();
void corrige_descendo(Heap h, int i);
void insert_process(Heap h, Process p);
void corrige_subindo(Heap h);
void corrige_descendo(Heap h, int i);
void constroi_min_heap(Heap h);
Process get_min(Heap h);
void SJF(Process *v, int size);

#endif
