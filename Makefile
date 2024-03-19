CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic -O2
# 128 MB stack
STACKFLAG = -Wl,--stack,134217728

NON_MAIN_SRCS = bitset.c error.c eratosthenes.c
SRCS = primes.c no-comment.c
OBJS = $(SRCS:.c=.o) $(NON_MAIN_SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	TARGETS = $(SRCS:.c=.exe) primes-i.exe
	RM = del /Q
else
	TARGETS = $(SRCS:.c=) primes-i
	RM = rm -f
endif

all: $(TARGETS)

# executables that need only their own object
%: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

# overwrite for those that need more
primes: primes.o eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -o $@ $^

primes.exe: primes.o eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -o $@ $^

primes-i: primes.o eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -DUSE_INLINE -o $@ $^

primes-i.exe: primes.o eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -DUSE_INLINE -o $@ $^

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^

no-comment.exe: no-comment.o error.o
	$(CC) $(CFLAGS) -o $@ $^

# objects only need the own .c and .h
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./primes
	./primes-i

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGETS)
