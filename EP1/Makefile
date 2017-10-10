default: all

ep1sh:
	gcc ep1sh.c ep1sh.h -lreadline -o ep1sh

ep1:
	gcc ep1.c ep1.h timer.c timer.h RR.c RR.h SJF.c SJF.h PS.c PS.h process.c process.h heap.c heap.h -lpthread -o ep1

all:
	gcc ep1sh.c ep1sh.h -lreadline -o ep1sh
	gcc ep1.c ep1.h timer.c timer.h RR.c RR.h SJF.c SJF.h PS.c PS.h process.c process.h heap.c heap.h -lpthread -o ep1

clean:
	rm ep1 ep1sh

update: clean
	git add *
