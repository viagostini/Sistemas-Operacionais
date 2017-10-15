
N=$1
D=$2
V=$3

make

echo '\nTestando com parametros { N =' $N ' D =' $D ' V =' $V '}\n'

erro="ERRO na execução do ep"


if [ ! -d "results" ]; then
    mkdir results
fi

if [ ! -d "debug" ]; then
    mkdir debug
fi

for T in `seq 1 4`; do
    echo 'Rodando teste' $T'!\n'
    ./ep2 $N $D $V d > results/result_$T 2> debug/debug_$T || echo $erro.$SCHED.$T

done

echo 'Script finalizado!\n'
