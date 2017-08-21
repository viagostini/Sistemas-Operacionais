default: sh

sh:
	gcc ep1sh.c ep1sh.h -lreadline -o ep1sh

ep:
	gcc ep.c ep.h timer.c RR.c RR.h process.c process.h -o ep
