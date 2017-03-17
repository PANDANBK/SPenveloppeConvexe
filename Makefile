CC=gcc
DEPS = hull.h graham.h jarvis.h

%.o: %.c $(DEPS)
	$(CC) -c -Wall -g -o $@ $<
all: pilote
pilote: pilote.o vecset.o vector.o graham.o jarvis.o
	$(CC) -Wall -g -std=c99 -o pilote pilote.o vecset.o vector.o graham.o jarvis.o -lm
clean:
	rm *.o
mrproper: clean
	rm pilote
