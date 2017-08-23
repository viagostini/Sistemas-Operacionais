#include "SJF.h"

int parent(int i);
int left_child(int i);
int right_child(int i);
Heap create_heap();
void corrige_descendo(Heap h, int i);
void insert_process(Heap h, Process p);
void corrige_subindo(Heap h);
void corrige_descendo(Heap h, int i);
void constroi_min_heap(Heap h);

int parent(int i) {
    return i/2;
}

int left_child(int i) {
    return 2*i;
}

int right_child(int i) {
    return 2*i + 1;
}

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
    while (i >= 2 && compare_process(h->A[i], h->A[i/2])) {
        swap_process(h->A[i/2], h->A[i]);
        i /= 2;
    }
}

void constroi_min_heap(Heap h) {
    int i;
    for (i = h->size / 2; i >= 1; i--)
        corrige_descendo(h, i);
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
            swap_process(h->A[j], h->A[f]);
            j = f;
        }
    }
}

void SJF(Process *v, int size) {
    int i;
    float timestamp; /* TO DO: Arrumar um nome melhor */
    struct timespec init, now;
    Heap h;

    h = create_heap();
    clock_gettime(CLOCK_MONOTONIC, &init);

    while(h->size > 0 || i < size) {
        timestamp = timer_check(init);

        while (i < size && v[i]->t0 <= timestamp) {
            insert_process(h, v[i++]);
        }

        Process p = get_min(h);
        if (p != NULL) {


            
        }
    }
}
