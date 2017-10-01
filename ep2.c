#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct ciclista {
    int lap;
    int pos;
    int speed;
} Ciclista;

int n;              /* Número de ciclistas */
int d;              /* Comprimento da pista */
int v;              /* Número de voltas */
int **track;        /* Matriz d x 10 */
int *racers;        /* Vetor de ciclistas */

int counter;
int globalsense = 0;

pthread_t *tid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double timer;       /* Milisegundos */

void update_position(int idx, int speed) {
    int x = racers[i].pos;
    racers[i].pos = (x + speed) % d;
    if (racers[i].pos < x)
        racers[i].lap++;
}

void *race (void *a) {
    int localsense = 0;
    int i = (int) a;
    int r = 0;
    printf("[ Thread %d ] criada!\n", i);
    while (1) {
        localsense = !localsense;
    
        pthread_mutex_lock(&mutex);
        update_position(i, racers[i].speed);          /* Seção crítica */
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        counter--;                                    /* Seção crítica */
        pthread_mutex_unlock(&mutex);
       
        if (!counter) {
            counter = n;
            globalsense = localsense;
        } 
        else while (globalsense != localsense);
    }
    printf("[ Thread %d ] terminou!\n", i);
    pthread_exit(NULL);
}


int main(int argc, char **argv){
    int i;

    n = atoi(argv[1]);
    d = atoi(argv[2]);

    counter = n;

    tid = malloc(n * sizeof(pthread_t));
    racers = malloc(n * sizeof(ciclista));

    for (i = 0; i < n; i++) {
        racers[i] = malloc(sizeof(ciclista));
        racers[i].speed = 1;
        racers[i].pos = 0;
        racers[i].lap = 1;
    }

    for (i = 0; i < n; i++)
        pthread_create(&tid[i], NULL, race, (void*)i);

    for (i = 0; i < n; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
