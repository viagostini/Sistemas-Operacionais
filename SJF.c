

void SJF(Process *v, int size) {
    float time = 0.0;





}

Heap create_heap() {
    Heap h = (Heap*) malloc (sizeof (Heap*));
    h->p = (Process*) malloc (sizeof (Process*) * 100);
    h->size = 0;
    h->max_size = 100;
    return h;
}

void destroy_heap(Heap h) {
    int i;
    for (i = 0; i < h->max_size; i++)
        free(h->(*p));
    free(h->p);
}

int parent(int i) {
    return i/2;
}

int left_child(int i) {
    return 2*i;
}

int right_child(int i) {
    return 2*i + 1;
}

Process remove_heap(Heap h) {
    Process max = h->p[1];
    h->p[1] = h->p[h->size];
    (h->size)--;
    down(h->p, h->size, 1);
    return max;
}
