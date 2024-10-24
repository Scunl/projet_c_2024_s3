CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = engine.o inoutput.o main.o
DEPS = incognito.h

main: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o main
