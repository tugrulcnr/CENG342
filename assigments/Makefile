CC = mpicc
CFLAGS = -Wall -Werror -std=c99 -I.

DEPS = hellomake.h

%.o: %.c $(DEPS)
$(CC) -c -o $@ $< $(CFLAGS)

all: program hellomake

program: 18050111002.o
$(CC) $(CFLAGS) -o $@ $^

18050111002.o: 18050111002.c
$(CC) $(CFLAGS) -c $< -o $@

hellomake: 18050111002.o hellofunc.o
$(CC) -o hellomake 18050111002.o hellofunc.o

clean:
rm -f program hellomake *.o
