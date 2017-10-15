# Le arquivos do tipo result_x_y_z_w.txt e produz dois arquivos:
#
# tempo_x_y_z.txt contem a media de tempo de execucao para
# as simulacoes de parametro n = x, d = y e v = z
#
# memoria_x_y_z.txt contem a media da quantidade usada de memoria ao
# executar as simulacoes de parametro n = x, d = y e v = z
#

import sys
import math

tempos = []
memorias = []

n = sys.argv[1]
d = sys.argv[2]
v = sys.argv[3]

num = 4

for i in xrange(1, num):
    tempo_file_path = "".join(['tempos/tempo_', n, '.', d, '.', v, '.', str(i)])
    #memoria_file_path = "".join(['memoria/memoria_', n, '.', d, '.', v, '.', str(i)])

    with open(tempo_file_path, 'r') as f:
        tempos.append(float(f.read().split('\n')[-2]))

    #with open(memoria_file_path, 'r') as f:
    #    memorias.append(float(last = f.read().split('\n')[-2]))

media_tempo = sum(tempos)/num
#media_memoria = sum(memorias)/30

print 'Media de tempo de execucao:', media_tempo, 's'
#print 'Media de memoria usada:', media_memoria, '\n'

std_tempo = math.sqrt(sum((media_tempo - tempo) ** 2.0 for tempo in tempos) / (num-1))
#std_memoria = math.sqrt(sum((media_finished - memoria) ** 2.0 for memoria in memorias) / (num-1))

print 'Desvio padrao do tempo de execucao:', std_tempo
#print 'Desvio padrao de processos finalizados:', std_memoria, '\n'

# Intervalos de confianca - media +/- 1,96 * std/sqrt(n)
offset_tempo = 1.96 * (std_tempo / math.sqrt(num))
#offset_memoria = 1.96 * (std_memoria / math.sqrt(num))

print 'Intervalo de confianca para tempo de execucao: (', \
    media_tempo - offset_tempo, ',', media_tempo + offset_tempo,\
    ')'
#print 'Intervalo de confianca para processos finalizados: (', \
#    media_finished - offset_memoria, ',', media_finished + offset_memoria,\
#    ')'
