# /*
#  *  Exercício Programa 3 - Sistemas Operacionais
#  *
#  *  Marcelo Baiano Pastorino Trylesinski |  9297996
#  *  Vinicius Perche de Toledo Agostini   |  4367487
#  *
#  */

.SUFFIXES: .java .class

.java.class:
	javac -g $*.java

CLASSES = \
    MemoryManager.java \
	FreeSpaceManager.java \
	PagingManager.java \
	BestFit.java \
	WorstFit.java \
	QuickFit.java \
	Optimal.java \
	FIFO.java \
	LRU4.java \
    MemBlock.java \
	Process.java \
	Event.java \
	Page.java \

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
