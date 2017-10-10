#include "heap.h"
#include "process.h"
#include <stdlib.h>

static void corrige_descendo(Heap h, int i);
static void corrige_subindo(Heap h);
Heap create_heap();
void insert_process(Heap h, Process p);
Process get_min(Heap h);
void print_heap(Heap h);

const int HEAP_SIZE = 101;

Heap create_heap() {
    Heap h = malloc(sizeof(Heap*));
    h->A = malloc(HEAP_SIZE * sizeof(Process*));
    h->size = 0;
    h->max_size = HEAP_SIZE - 1;
    return h;
}

void insert_process(Heap h, Process p) {
    h->size++;
    if (h->size == h->max_size) {
        h->max_size += 1;
        h->A = realloc(h->A, 2 * h->max_size * sizeof(Process*));
        h->max_size = (h->max_size * 2) - 1;
    }
    h->A[h->size] = p;
    corrige_subindo(h);
}

void corrige_subindo(Heap h) {
    int i = h->size;
    while (i >= 2 && !compare_process(h->A[i/2], h->A[i])) {
        Process p = h->A[i/2];
        h->A[i/2] = h->A[i];
        h->A[i] = p;
        i /= 2;
    }
}

void corrige_descendo(Heap h, int i) {
    int j = i;
    while (2 * j <= h->size) {
        int f = 2 * j;
        if (f < h->size && compare_process(h->A[f + 1], h->A[f]))
            f = f + 1;
        if (compare_process(h->A[j], h->A[f]))
            j = h->size;
        else {
            Process p = h->A[j];
            h->A[j] = h->A[f];
            h->A[f] = p;
            j = f;
        }
    }
}

Process get_min(Heap h) {
    if(h->size == 0)
        return NULL;
    Process p = h->A[1];
    h->A[1] = h->A[h->size];
    h->size--;
    corrige_descendo(h, 1);
    return p;
}

void print_heap(Heap h) {
    int i;
    for (i = 1; i <= h->size; i++)
        printf("%s: %f\n", h->A[i]->name, h->A[i]->dt);
}
