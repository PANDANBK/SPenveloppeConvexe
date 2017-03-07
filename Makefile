CC=gcc
DEPS = hull.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<
all: vecset
vecset: vecset.o vector.o
	$(CC) -g -std=c99 -o vecset vecset.o vector.o
clean:
	rm *.o
mrproper: clean
	rm vecset
