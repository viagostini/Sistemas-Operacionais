default: sh

sh:
	gcc ep1sh.c ep1sh.h -lreadline -o ep1sh
	gcc ep.c ep.h timer.c timer.h RR.c RR.h SJF.c SJF.h PS.c PS.h process.c process.h heap.c heap.h -lpthread -o ep

clean:
	rm ep ep1sh

update: clean
	git add *
