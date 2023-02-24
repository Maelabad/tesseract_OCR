
all: main.o script.o 
	gcc main.o script.o -o Programme

main.o: main.c
	gcc -c main.c -o main.o

script.o: script.c
	gcc -c script.c -o script.o


clean:
	rm -rf *.o

mrproper: clean
	rm -rf Programme
