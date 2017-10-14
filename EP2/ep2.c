/*
 *  Exercício Programa 2 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

/*
    TODO
    - O PRINT DA MAIN TA FORA DO Tempo
        -> Join não funciona direito
    - Print final
    - Sistema de Pontuação - implementado
        -> Bonus por ultrapassar geral
    - Testes
    - Apresentação
    - Scripts
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

struct ciclista {
    int id;
    int dt;
    int lap;
    int pos;
    int speed;          /* Tempo em ms que leva para andar 1 metro */
    int score;          /* Pontuação acumulada */
};

typedef struct ciclista *Ciclista;


int exited = 0;
int finished = 0;
int lap_completed = -1;

int DEBUG = 0;

int N;                  /* Número total de ciclistas */
int n;                  /* Número de ciclistas ainda correndo */
int d;                  /* Comprimento da pista */
int v;                  /* Número de voltas */
int **track;            /* Matriz d x 10 */
int **ult;              /* ult[i][j] := # de vezes que i ultrapassou j */
Ciclista* racers;       /* Vetor de ciclistas */

int flash = -1;

int counter;
int globalsense = 0;

pthread_t *tid;
pthread_mutex_t mutex;

Ciclista cria_ciclista(int i) {
    Ciclista x = malloc(sizeof(Ciclista*));

    x->id = i;

    if (i < 10) {
        /* Ciclistas na primeira fileira já ultrapassaram os outros 1 vez */
        x->lap = 1;
        x->pos = i / 10;
    } else {
        x->lap = 0;
        x->pos = d-(i/10);
    }

    x->score = 0;
    x->speed = 120;
    x->dt = x->speed;

    return x;
}

void print_track() {
    int i, j;

    for (i = 0; i < d; i++) {
        for (j = 0; j < 10; j++) {
            if (track[i][j] == -1)
                printf("-- ");
            else
                printf("%2d ", track[i][j]);
        }
        printf("\n");
    }
}

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
    int new_pos = (racers[i]->pos + 1) % d;

    for (j = col + 1; j < 10; j++)
        if (track[new_pos][j] == -1)
            return j;

    return -1;
}

int find_col(int i) {
    int j;

    for (j = 0; j < 10; j++)
        if (track[racers[i]->pos][j] == i)
            return j;

    return -1;
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
        col = find_col(i);

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
            } else {
                racers[i]->speed = racers[track[new_pos][col]]->speed;
                track[prev_pos][col] = i;
            }
        }

        if (racers[i]->pos < prev_pos) {
            racers[i]->lap++;

            lap_completed = i;

            /* Se ciclista terminou, retira de track[][] */
            if (racers[i]->lap > v) {
                finished++;
                track[racers[i]->pos][find_col(i)] = -1;
            }

	        if (racers[i]->lap % 15 == 0 && n > 5) {
        		if (rand() % 100 < 1) {
                    int more = 0;
                    for (j = 0; j < N; j++)
                        if (racers[j]->score > racers[i]->score)
                            more++;
                    printf("[ Ciclista %d ] quebrou na volta %d!\n", i, racers[i]->lap);
                    printf("[ Ciclista %d ] estava na posição %d por pontos!\n", more+1);
        		    n--;
                    track[racers[i]->pos][find_col(i)] = -1;
        		    pthread_mutex_unlock(&mutex);
        		    pthread_exit(NULL);
        		}
            }
            if (racers[i]->lap > 1)
                update_speed(i);
        }
        racers[i]->dt = racers[i]->speed;
    }
    if (DEBUG) {
        printf("\n--------------  TRACK  --------------\n\n");
        print_track();
    }
}

int compare_score (const void *a, const void *b) {
    Ciclista nA, nB;

    nA = *((Ciclista *) a);
    nB = *((Ciclista *) b);

    return (nB->score - nA->score);
}

int compare_position (const void *a, const void *b) {
    Ciclista nA, nB;

    nA = *((Ciclista *) a);
    nB = *((Ciclista *) b);

    if (nA->lap > nB->lap)
        return -1;

    if (nA->lap < nB->lap)
        return 1;

    return nB->pos - nA->pos;
}

Ciclista *sort_by_pos() {
    int i;

    Ciclista *arr = malloc(N * sizeof(Ciclista));

    for (i = 0; i < N; i++) {
        arr[i] = malloc(sizeof(Ciclista*));
        *arr[i] = *racers[i];
    }

    qsort(arr, N, sizeof(Ciclista*), compare_position);

    return arr;
}

void calculate_score() {
    int i;
    Ciclista *arr = sort_by_pos();

    racers[arr[0]->id]->score += 5;
    racers[arr[1]->id]->score += 3;
    racers[arr[2]->id]->score += 2;
    racers[arr[3]->id]->score += 1;

    for (i = 0; i < N; i++)
        free(arr[i]);
    free(arr);
}

void print_score() {
    if (lap_completed != -1 &&
            racers[lap_completed]->lap % 2 == 0 &&
            racers[lap_completed]->lap > 1) {

        int i;

        calculate_score();

        Ciclista *arr = malloc(N * sizeof(Ciclista));

        for (i = 0; i < N; i++) {
            arr[i] = malloc(sizeof(Ciclista*));
            *arr[i] = *racers[i];
        }

        qsort(arr, N, sizeof(Ciclista*), compare_score);

        for (i = 0; i < N; i++) {
            printf("[ Ciclista %d ] -> %d pontos!\n", arr[i]->id, arr[i]->score);
            free(arr[i]);
        }
        free(arr);
    }
}

void print_position() {
    if (lap_completed != -1) {
        int i;
        Ciclista *arr = sort_by_pos();
        for (i = 0; i < N; i++) {
            printf("%dº -> [ Ciclista %d ]\n", i+1, arr[i]->id);
            free(arr[i]);
        }
        free(arr);
    }
    lap_completed = -1;
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

        counter--;
        update_position(i);          /* Seção crítica */
        printf("[ Corredor %d ] está na posição %d.\n", i, racers[i]->pos);
        usleep(10000);

        if (racers[i]->lap > v)
	        n--;

        if (counter == 0) {
            print_score();
            print_position();
            counter = n;
            globalsense = localsense;
            pthread_mutex_unlock(&mutex);
	        if (racers[i]->lap > v) break;
        }
        else {
            pthread_mutex_unlock(&mutex);
            if (racers[i]->lap > v)
                break;
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
    pthread_mutex_lock(&mutex);
    exited++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}


int main(int argc, char **argv){
    int i, j;
    int a = 0;

    N = n = atoi(argv[1]);
    d = atoi(argv[2]);
    v = atoi(argv[3]);

    if (argc == 5 && argv[4][0] == 'd')
        DEBUG = 1;

    counter = N;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    tid = malloc(N * sizeof(pthread_t));
    racers = malloc(N * sizeof(Ciclista));
    track = malloc(d * sizeof(int*));
    ult = malloc(N * sizeof(int*));

    for (i = 0; i < d; i++)
        track[i] = malloc(10 * sizeof(int));

    for (i = 0; i < d; i++)
        for (j = 0; j < 10; j++)
            track[i][j] = -1;

    for (i = 0; i < n; i++) {
        ult[i] = malloc(N * sizeof(int));
    	racers[i] = cria_ciclista(i);
        if (i < 10)
            track[0][i] = i;
        else
            track[d-(i/10)][i%10] = i;
    }

    if (rand() % 100 < 10) {
        flash = rand() % n;
        printf("(Corredor %d) -> Flash\n", flash);
    }

    for (i = 0; i < n; i++) {
	int *arg = malloc(sizeof(int*));
	*arg = i;
        if (pthread_create(&tid[i], NULL, race, (void *)arg)) {
            printf("\n ERROR creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < n; i++) {
        if (pthread_join(tid[i], NULL)) {
            printf("\n ERROR joining thread");
            exit(EXIT_FAILURE);
        } else {
            a++;
        }
    }

    while(a < n);
    printf("Finished = %d\n", finished);
    printf("Exited = %d\n", exited);

    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}
