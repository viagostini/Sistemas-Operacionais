#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

/* Como executar?
    ./input N T
    Sendo N o número de processos em cada teste.
    Sendo T o número de testes.
*/
int main(int argc, char* argv[]) {
    FILE* f_open;
    int N, T, proc;
    double t0, dt, deadline;

    if (argc < 3) {
        fprintf(stderr, "%s\n", "Envie o número de processos em cada teste e o número de testes");
        exit(1);
    }
    N = atoi(argv[1]);
    T = atoi(argv[2]);
    srand (time(NULL));

    for (int i = 0; i < T; i++) {
        string name = "./Testes/teste";
        stringstream out;
        out << i;
        name += (out.str() + ".txt");
        f_open = fopen(name.c_str(), "w");
        for (int j = 0; j < N; j++) {
            t0 = ((double)j/3.0)*0.2;
            dt = 0.2 + (double)(rand() % 15 + 1) * 0.2;
            deadline = t0 + dt + (double)(rand() % 10 + 1)*0.1;
            fprintf(f_open, "%f %f %f processo%d\n", t0, dt, deadline, j);
        }
        fclose(f_open);
    }

    return 0;
}
