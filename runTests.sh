# Primeiro argumento é o escalonador.
# Segundo argumento é quantos testes rodar.
# Exemplo: ./runTests.sh 2 5
# Roda ep com o escalonador 2 para os arquivos 1,2,3,4,5.

SCHED=$1
TEST=$2

echo Testando escalonador $SCHED

erro="ERRO na execução do ep"

make

if [ ! -d "results" ]; then
    mkdir results
fi

for T in seq $TEST; do
    trace_file=Testes/teste$T.txt
    result_file=results/result_file_$SCHED.$T.txt

    echo Rodando teste $T com algoritmo $SCHED!

    ./ep $SCHED $trace_file $result_file || echo $erro.$SCHED.$T

done

echo Teste $T do algoritmo $SCHED finalizado!
