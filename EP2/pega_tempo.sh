# Script pra pegar o tempo de ./runTests n d v

n=$1
d=$2
v=$3

if [ ! -d "tempos" ]; then
    mkdir tempos
fi

if [ ! -d "results" ]; then
    mkdir results
fi

if [ ! -d "debug" ]; then
    mkdir debug
fi

make

echo $'\nTestando com parametros { N =' $n ' D =' $d ' V =' $v $'}\n'


for T in `seq 1 30`; do
    echo 'Rodando teste' $T'!\n'
    (/usr/bin/time -f "%e" ./ep2 $n $d $v) 2>> tempos/tempo_$n.$d.$v
done

echo 'Script finalizado!\n'
