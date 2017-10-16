/*
 *  Exercício Programa 2 - Sistemas Operacionais
 *
 *  Marcelo Baiano Pastorino Trylesinski |  9297996
 *  Vinicius Perche de Toledo Agostini   |  4367487
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

/* ------------------------------------------------------------------------- */
/* --------------------------  VARIÁVEIS GLOBAIS  -------------------------- */
/* ------------------------------------------------------------------------- */

struct ciclista {
    int id;
    int dt;
    int lap;
    int pos;
    int speed;          /* Tempo em ms que leva para andar 1 metro */
    int score;          /* Pontuação acumulada */
};

typedef struct ciclista *Ciclista;

int finished = 0;
int lap_completed = -1;

int DEBUG = 0;

int N;                  /* Número total de ciclistas */
int n;                  /* Número de ciclistas ainda correndo */
int d;                  /* Comprimento da pista */
int v;                  /* Número de voltas */
int **track;            /* Matriz d x 10 */
int *time_ciclista;     /* Tempo de corrida de cada ciclista */
int *lap_diff;
Ciclista* racers;       /* Vetor de ciclistas */

int flash = -1;

int counter;
int globalsense = 0;

pthread_t *tid;
pthread_mutex_t mutex;

/* -------------------------------------------------------------------------- */
/* ------------------------------  PROTÓTIPOS  ------------------------------ */
/* -------------------------------------------------------------------------- */

/* A função has_bonus() verifica se o ciclista i deve ganhar pontos bônus. */
void has_bonus(int i);

/* A função print_finish() imprime na tela as pontuações finais. */
void print_finish();

/* A função cria_ciclista() cria um ciclista com id i e devolve esse ciclista. */
Ciclista cria_ciclista(int i);

/* A função print_track() imprime na tela a pista. As posições com '--' sinalizam
// posições sem ciclistas e os números representam os ciclistas. */
void print_track();

/* A função update_speed() atualiza a velocidade do ciclista i. */
void update_speed(int i);

/* A função can_overtake() verifica se o ciclista i pode fazer a ultrapassagem
// em alguma faixa com valor maior que col. Devolve -1 caso não encontre nenhuma
// faixa possível ou o número da faixa encontrada. */
int can_overtake(int i, int col);

/* A função find_col() encontra a faixa em que o ciclista i está. */
int find_col(int i);

/* A função update_position() atualiza a posição do ciclista i. */
void update_position(int i);

/* A função compare_score() compara os ciclistas a e b. Devolve a subtração
// da pontuação de b pela de a. */
int compare_score(const void *a, const void *b);

/* A função compare_position() compara os ciclistas a e b. Devolve um número
// positivo caso b esteja na frente de a e negativo caso contrário. */
int compare_position(const void *a, const void *b);

/* A função sort_by_pos() devolve um vetor de ciclistas ordenado pela posição. */
Ciclista *sort_by_pos();

/* A função calculate_score() atualiza a pontuação de cada ciclista. */
void calculate_score();

/* A função print_score() imprime na tela a pontuação de todos os ciclistas. */
void print_score();

/* A função print_position() imprime na tela a posição de todos os ciclistas. */
void print_position();

/* A função race() é a thread do ciclista a. */
void *race(void *a);

/* -------------------------------------------------------------------------- */
/* ---------------------------------  MAIN  --------------------------------- */
/* -------------------------------------------------------------------------- */

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
    lap_diff = malloc(N * sizeof(int));
    time_ciclista = malloc(N * sizeof(int));

    for (i = 0; i < d; i++)
        track[i] = malloc(10 * sizeof(int));

    for (i = 0; i < d; i++)
        for (j = 0; j < 10; j++)
            track[i][j] = -1;

    for (i = 0; i < N; i++) {
        time_ciclista[i] = 0;
        lap_diff[i] = 2;
    	racers[i] = cria_ciclista(i);
        if (i < 10)
            track[0][i] = i;
        else
            track[d-(i/10)][i%10] = i;
    }

    if (rand() % 100 < 10)
        flash = rand() % N;

    for (i = 0; i < N; i++) {
        int *arg = malloc(sizeof(int*));
        *arg = i;
        if (pthread_create(&tid[i], NULL, race, (void *)arg)) {
            fprintf(stderr, "%s", "\n ERROR creating thread");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < N; i++) {
        if (pthread_join(tid[i], NULL)) {
            fprintf(stderr, "%s", "\n ERROR joining thread");
            exit(EXIT_FAILURE);
        }
    }

    finished = 1;
    print_finish();

    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    free(tid);
    free(racers);
    for (j = 0; j < d; j++)
        free(track[j]);
    free(track);
    free(lap_diff);
    free(time_ciclista);

    return 0;
}

/* ------------------------------------------------------------------------- */
/* -------------------------------  FUNÇÕES  ------------------------------- */
/* ------------------------------------------------------------------------- */

void print_finish() {
    int i;

    print_score();

    for (i = 0; i < N; i++) {
        if (time_ciclista[i] < 0)
            printf("[ Ciclista %d ] quebrou na volta %d\n", i, racers[i]->lap);
        else
            printf("[ Ciclista %d ] terminou no tempo %dms\n", i, time_ciclista[i]);
    }
}

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
                fprintf(stderr, "-- ");
            else
                fprintf(stderr, "%2d ", track[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

void update_speed(int i) {
    int prev = racers[i]->speed;

    int r = rand() %  100;

    if (prev == 120) {
        if (r < 70)
            racers[i]->speed = 60;
    } else if (prev == 60) {
        if (r < 50)
            racers[i]->speed = 120;
    }

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

    if ((flash != -1) && (racers[flash]->lap >= v - 1)) {
        time_ciclista[i] += 20;
        racers[i]->dt -= 20;
    } else {
        time_ciclista[i] += 60;
        racers[i]->dt -= 60;
    }

    if (racers[i]->dt == 0) {
        col = find_col(i);

        track[prev_pos][col] = -1;

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

            has_bonus(lap_completed);

            /* Se ciclista terminou, retira de track[][] */
            if (racers[i]->lap > v)
                track[racers[i]->pos][find_col(i)] = -1;

            if (racers[i]->lap % 15 == 0 && n > 5) {
                if (rand() % 100 < 1) {
                    int more = 0;
                    for (j = 0; j < N; j++)
                    if (racers[j]->score > racers[i]->score)
                        more++;
                    printf("[ Ciclista %d ] quebrou na volta %d!\n", i, racers[i]->lap);
                    printf("[ Ciclista %d ] estava na posição %d por pontos!\n", i, more+1);
                    n--;
                    track[racers[i]->pos][find_col(i)] = -1;
                    time_ciclista[i] *= -1;
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
        fprintf(stderr, "\n--------------  TRACK  --------------\n\n");
        print_track();
    }
}

void has_bonus(int i) {
    int j;
    Ciclista *arr = sort_by_pos();

    if (arr[0]->id == i)
        for (j = 0; j < N; j++)
            if (i != j && lap_diff[i] == racers[i]->lap - racers[j]->lap) {
                lap_diff[i]++;
                racers[i]->score += 20;
            }

    for (j = 0; j < N; j++)
        free(arr[j]);
    free(arr);
}

int compare_score(const void *a, const void *b) {
    Ciclista nA, nB;

    nA = *((Ciclista *) a);
    nB = *((Ciclista *) b);

    return (nB->score - nA->score);
}

int compare_position(const void *a, const void *b) {
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
    if ((lap_completed != -1 &&
        racers[lap_completed]->lap % 10 == 0 &&
        racers[lap_completed]->lap > 1) ||
        finished) {

            int i;

            calculate_score();

            Ciclista *arr = malloc(N * sizeof(Ciclista));

            for (i = 0; i < N; i++) {
                arr[i] = malloc(sizeof(Ciclista*));
                *arr[i] = *racers[i];
            }

            qsort(arr, N, sizeof(Ciclista*), compare_score);

            printf("\n-------- PONTUAÇÃO --------\n\n");
            for (i = 0; i < N; i++) {
                printf("[ Ciclista %d ] -> %d pontos!\n", arr[i]->id, arr[i]->score);
                free(arr[i]);
            }
            free(arr);
            printf("\n--------------------------\n");
        }
    }

void print_position() {
        if (lap_completed != -1) {
            int i;
            Ciclista *arr = sort_by_pos();
            printf("\n-------- POSIÇÕES --------\n\n");
            for (i = 0; i < N; i++) {
                printf("%dº -> [ Ciclista %d ]\n", i+1, arr[i]->id);
                free(arr[i]);
            }
            free(arr);
            printf("\n--------------------------\n");
        }
        lap_completed = -1;
    }

void *race(void *a) {
        int localsense = 0;
        int i = *((int *) a);
        int r = 0;

        free(a);
        while (1) {
            localsense = 1 - localsense;
            pthread_mutex_lock(&mutex);
            counter--;
            update_position(i);

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
                while (globalsense != localsense) usleep(10);
            }
        }
        return NULL;
    }
