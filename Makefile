CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o building.o container.o sort.o io.o

all: program

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

building.o: building.c building.h
	$(CC) $(CFLAGS) -c building.c

container.o: container.c container.h
	$(CC) $(CFLAGS) -c container.c

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c sort.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f *.o program
