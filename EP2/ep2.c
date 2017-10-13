/*  
 *  Exercício Programa 2 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

/*
    TODO
    - Sistema de Pontuação
        -> Bonus por ultrapassar geral
    - Ciclistas quebrando (implementado +-)
    - Flash (ver se tá tudo certo)
    - Debug
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct ciclista {
    int dt;
    int lap;
    int pos;
    int speed;          /* Tempo em ms que leva para andar 1 metro */
    int score;          /* Pontuação acumulada */
};

typedef struct ciclista *Ciclista;

Ciclista cria_ciclista(int i) {
    Ciclista x = malloc(sizeof(Ciclista*));

    x->lap = 1;
    x->score = 0;
    x->speed = 120;
    x->pos = i / 10;
    x->dt = 120;

    return x;
}

int n;                  /* Número de ciclistas */
int d;                  /* Comprimento da pista */
int v;                  /* Número de voltas */
int **track;            /* Matriz d x 10 */
Ciclista* racers;       /* Vetor de ciclistas */

int flash = -1;

int counter;
int globalsense = 0;

pthread_t *tid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void update_speed(int i) {
    int prev = racers[i]->speed;

    int r = rand() %  100;

    if (prev == 120)
        if (r < 70)
            racers[i]->speed = 60;
    else if (prev == 60)
        if (r < 50)
            racers[i]->speed = 120;

    if ((flash != -1) && (racers[flash]->lap == v - 1))
        racers[flash]->speed = 40;
}

int can_overtake(int i, int col) {
    int j;
    int new_col = -1;
    int new_pos = (racers[i]->pos + 1) % d;

    for (j = col + 1; j < 10; j++)
        if (track[new_pos][j] == -1)
            new_col = j;

    return new_col;
}

void update_position(int i) {
    int j, col, new_col;
    int prev_pos = racers[i]->pos;
    int new_pos = (prev_pos + 1) % d;

    if ((flash != -1) && (racers[flash]->lap >= v - 1))
        racers[i]->dt -= 20;
    else
        racers[i]->dt -= 60;

    if (racers[i]->dt == 0) {
        for (j = 0; j < 10; j++)
            if (track[prev_pos][j] == i)
                col = j;

        track[prev_pos][col] = -1;

        /*  se não tiver ninguem na frente
              racers[i]->pos = (prev_pos + 1) % d;
            caso contrario
              posso ultrapassar
                ultrapassa
            não posso ultrapassar
                reduz velocidade
        */

        if (track[new_pos][col] == -1) {
            racers[i]->pos = new_pos;
            track[new_pos][col] = i;
        } else {
            if ((new_col = can_overtake(i, col)) != -1) {
                racers[i]->pos = new_pos;
                track[new_pos][new_col] = i;
            } else
                racers[i]->speed = racers[track[new_pos][col]]->speed;
        }

        if (racers[i]->pos < prev_pos) {
            racers[i]->lap++;
	    if (racers[i]->lap % 2 == 0 && n > 5)
		if (rand() % 100 < 90) {
		    printf("[ Ciclista %d ] quebrou!\n", i);
		    n--;
		    counter--;
		    pthread_mutex_unlock(&mutex);
		    pthread_exit(NULL);
		}
            update_speed(i);
        }
    
        racers[i]->dt = racers[i]->speed;
    }

}

void *race (void *a) {
    int localsense = 0;
    int i = *((int *) a);
    int r = 0;

    free(a);
    printf("[ Corredor %d ] criado!\n", i);
    while (1) {
        localsense = 1 - localsense;

        pthread_mutex_lock(&mutex);

        update_position(i);          /* Seção crítica */
        printf("[ Corredor %d ] está na posição %d.\n", i, racers[i]->pos);
        counter--;
        usleep(10000);

        if (racers[i]->lap > v)
	    n--;
	
        if (counter == 0) {
            counter = n;
            globalsense = localsense;	
            pthread_mutex_unlock(&mutex);
	    if (racers[i]->lap > v) break;
        }
        else {
	    if (racers[i]->lap > v) {
		pthread_mutex_unlock(&mutex);
		break;
	    }
            pthread_mutex_unlock(&mutex);
            while (globalsense != localsense);
        }
    }
    //printf("--------------------------------\n");
    printf("[ Corredor %d ] terminou!\n", i);
    //    printf("GLOBALSENSE = %d\n", globalsense);
    //printf("LOCALSENSE = %d\n", localsense);
    //printf("COUNTER = %d\n", counter);
    //printf("N = %d\n", n);
    //printf("--------------------------------\n");
    pthread_exit(NULL);
}


int main(int argc, char **argv){
    int i, j;

    n = atoi(argv[1]);
    d = atoi(argv[2]);
    v = atoi(argv[3]);

    counter = n;
    srand(time(NULL));

    tid = malloc(n * sizeof(pthread_t));
    racers = malloc(n * sizeof(Ciclista));
    track = malloc(d * sizeof(int*));

    for (i = 0; i < d; i++)
        track[i] = malloc(10 * sizeof(int));

    for (i = 0; i < d; i++)
        for (j = 0; j < 10; j++)
            track[i][j] = -1;

    for (i = 0; i < n; i++) {
	racers[i] = cria_ciclista(i);
	track[i/10][i%10] = i;
    }

    if (rand() % 100 < 10) {
        flash = rand() % n;
        printf("(Corredor %d) -> FLASH IN DA HOUSE\n", flash);
    }

    for (i = 0; i < n; i++) {
	int *arg = malloc(sizeof(int*));
	*arg = i;
        if (pthread_create(&tid[i], NULL, race, (void *)arg)) {
            printf("\n ERROR creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < n; i++)
        if (pthread_join(tid[i], NULL)) {
            printf("\n ERROR joining thread");
            exit(EXIT_FAILURE);
        }

    return 0;
}
