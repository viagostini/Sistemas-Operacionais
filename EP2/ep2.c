/*  Exercício Programa 2 - Sistemas Operacionais
//  Marcelo Baiano Pastorino Trylesinski / 9297996
//  Vinicius Perche de Toledo Agostini / 4367487
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct ciclista {
    int lap;
    int pos;
    int speed; /* Tempo em ms que leva para andar 1 metro */
    int dt;
};

typedef struct ciclista *Ciclista;

int n;                  /* Número de ciclistas */
int d;                  /* Comprimento da pista */
int v;                  /* Número de voltas */
int **track;            /* Matriz d x 10 */
Ciclista* racers;       /* Vetor de ciclistas */

int counter;
int globalsense = 0;

pthread_t *tid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double timer;       /* Milisegundos */

void update_position(int i) {
    int j, col;
    int x = racers[i]->pos;

    for (j = 0; j < 10; j++)
        if (track[x][j] == i)
            col = j;

    track[x][col] = -1;

    racers[i]->pos = (x + racers[i]->speed) % d;
    if (racers[i]->pos < x)
        racers[i]->lap++;

    track[racers[i]->pos][col] = i;
}

void *race (void *a) {
    int localsense = 0;
    int i = *(int*) a ;
    int r = 0;
    printf("[ Corredor %d ] criado!\n", i);
    while (1) {
        localsense = !localsense;

        pthread_mutex_lock(&mutex);
        update_position(i);          /* Seção crítica */
        printf("[ Corredor %d ] está na posição %d.\n", i, racers[i]->pos);
        sleep(1);
        if (racers[i]->lap > v) break;
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
    printf("[ Corredor %d ] terminou!\n", i);
    pthread_exit(NULL);
}


int main(int argc, char **argv){
    int i, j;

    n = atoi(argv[1]);
    d = atoi(argv[2]);
    v = 2;

    counter = n;

    tid = malloc(n * sizeof(pthread_t));
    racers = malloc(n * sizeof(Ciclista));
    track = malloc(d * sizeof(int*));

    for (i = 0; i < d; i++)
        track[i] = malloc(10 * sizeof(int));

    for (i = 0; i < d; i++)
        for (j = 0; j < 10; j++)
            track[i][j] = -1;

    for (i = 0; i < n; i++) {
        racers[i] = malloc(sizeof(Ciclista*));
        racers[i]->speed = 120;
        racers[i]->pos = 0;
        racers[i]->lap = 1;
        racers[i]->dt = racers[i]->speed;
    }

    for (i = 0; i < n; i++) {
        track[i / 10][i % 10] = i;
        racers[i]->pos = i / 10;
    }

    for (i = 0; i < n; i++)
        if (pthread_create(&tid[i], NULL, race, &i)) {
            printf("\n ERROR creating thread");
            exit(EXIT_FAILURE);
        }

    for (i = 0; i < n; i++)
        if (pthread_join(tid[i], NULL)) {
            printf("\n ERROR joining thread");
            exit(EXIT_FAILURE);
        }

    return 0;
}
