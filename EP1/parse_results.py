# Le arquivos do tipo result_x_y.txt e produz dois arquivos:
#
# context_x_size.txt contem a media de mudancas de contexto para
# os traces de tamanho size (small, medium, large) usando o algoritmo x
#
# deadline_x_size.txt contem a media de processos que terminaram de
# executar antes de seu deadline nos traces de tamanho size (small,
# medium, large) usando o algoritmo x

import sys
import math

medias_context = []
medias_finished = []

sched = sys.argv[1]
begin = int(sys.argv[2])
end = int(sys.argv[3])

for i in xrange(begin, end):
    result_file_path = "".join(['results/result_novo_', sched, '.', str(i)])
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
