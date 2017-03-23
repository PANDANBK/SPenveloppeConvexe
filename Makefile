CC=gcc
DEPS = hull.h graham.h jarvis.h quickhull.h

%.o: %.c $(DEPS)
	$(CC) -c -Wall -g -o $@ $<
all: pilote
pilote: vector.o vecset.o graham.o jarvis.o quickhull.o pilote.o
	$(CC) -Wall -g -std=c99 -o pilote vector.o vecset.o graham.o jarvis.o quickhull.o pilote.o -lm
clean:
	rm *.o
mrproper: clean
	rm pilote
