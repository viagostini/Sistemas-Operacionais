default: sh

sh:
	gcc ep1sh.c ep1sh.h -lreadline -o ep1sh

clean:
	-rm -f ep1sh
