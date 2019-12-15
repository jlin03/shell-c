all:	shell.o main.o
		gcc -o program shell.o main.o

shell.o:	shell.c headers.h
		gcc -c shell.c

main.o: main.c headers.h
		gcc -c main.c

run:
		./program
		
clean:
		rm *.o
		rm *~
