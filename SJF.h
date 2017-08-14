#ifndef SJF_H
#define SJF_H

struct heap {
    Process *p;
    int size;
    int max_size;
};

typedef struct heap *Heap;

#endif 