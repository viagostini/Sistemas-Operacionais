# Le arquivos do tipo result_x_y_z_w.txt e produz dois arquivos:
#
# tempo_x_y_z.txt contem a media de tempo de execuçao para
# as simulaçoes de parametro n = x, d = y e v = z
#
# memoria_x_y_z.txt contem a media da quantidade usada de memoria ao
# executar as simulaço  es de parametro n = x, d = y e v = z
#

import sys
import math

medias_tempo = []
medias_memoria = []

n = sys.argv[1]
d = sys.argv[2]
v = sys.argv[3]

for i in xrange(1, 30):
    tempos_file_path = "".join(['tempos/tempo_', n, d, v, str(i)])
    with open(result_file_path, 'r') as f:
        last_two = f.read().split('\n')[-2:]
        medias_finished.append(int(last_two[0]))
        medias_context.append(int(last_two[1]))

media_context = sum(medias_context)/30
media_finished = sum(medias_finished)/30

print 'Media de mudancas de contexto:', media_context
print 'Media de processos finalizados:', media_finished, '\n'

std_context = math.sqrt(sum((media_context - context) ** 2.0 for context in medias_context) / 29)
std_finished = math.sqrt(sum((media_finished - finished) ** 2.0 for finished in medias_finished) / 29)

print 'Desvio padrao de mudancas de contexto:', std_context
print 'Desvio padrao de processos finalizados:', std_finished, '\n'

# Intervalos de confianca - media +/- 1,96 * std/sqrt(n)
offset_context = 1.96 * (std_context / math.sqrt(30))
offset_finished = 1.96 * (std_finished / math.sqrt(30))

print 'Intervalo de confianca para mudanca de contexto: (', \
    media_context - offset_context, ',', media_context + offset_context,\
    ')'
print 'Intervalo de confianca para processos finalizados: (', \
    media_finished - offset_finished, ',', media_finished + offset_finished,\
    ')'
