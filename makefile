build: tabellare.c tab.o klib
	gcc -o tabellare tabellare.c tab.o klib/klib.o

tab.o: klib tab.h tab.c
	gcc -c tab.c

klib:
	git clone "https://gitlab.com/kappanneo/klib.git"
	make -C klib
