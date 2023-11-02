CC = gcc
CFLAGS = -g -Wall
OBJ = main.o line.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

main.o: main.c line.h
	$(CC) $(CFLAGS) -c main.c

line.o: line.c line.h
	$(CC) $(CFLAGS) -c line.c

clean:
	rm -f *.o program
