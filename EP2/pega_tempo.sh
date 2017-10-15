# Script pra pegar o tempo de ./runTests n d v

n=$1
d=$2
v=$3

if [ ! -d "tempos" ]; then
    mkdir tempos
fi

(/usr/bin/time -f "%e" ./runTests.sh $n $d $v) &> tempos/tempo_$n.$d.$v
