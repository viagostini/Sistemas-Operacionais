# Primeiro argumento é o escalonador.
# Segundo argumento é quantos testes rodar.
# Exemplo: ./runTests.sh 2 5
# Roda ep com o escalonador 2 para os arquivos 1,2,3,4,5.

SCHED=$1
TEST=$2

echo '\nTestando escalonador' $SCHED '\n'

erro="ERRO na execução do ep"

make

if [ ! -d "results" ]; then
    mkdir results
fi

if [ ! -d "debug" ]; then
    mkdir debug
fi

for T in `seq 1 $TEST`; do
    #trace_file=Testes/teste$T.txt
    trace_file=traces/trace_file_$T.txt
    result_file=results/result_$SCHED.$T.txt

    echo '\nRodando teste' $T 'com algoritmo' $SCHED'!\n'

    ./ep $SCHED $trace_file $result_file d 2> debug/debug_$SCHED.$T || echo $erro.$SCHED.$T

done

echo 'Script finalizado!\n'
