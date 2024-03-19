CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic -O2
# 128 MB stack
STACKFLAG = -Wl,--stack,134217728

NON_MAIN_SRCS = bitset.c error.c
SRCS = eratosthenes.c no-comment.c
OBJS = $(SRCS:.c=.o) $(NON_MAIN_SRCS:.c=.o)

ifeq ($(OS),Windows_NT)
	TARGETS = $(SRCS:.c=.exe)
	RM = del /Q
else
	TARGETS = $(SRCS:.c=)
	RM = rm -f
endif

all: $(TARGETS)

# executables that need only their own object
%: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

# overwrite for those that need more
eratosthenes: eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -o $@ $^

eratosthenes.exe: eratosthenes.o bitset.o error.o
	$(CC) $(CFLAGS) $(STACKFLAG) -o $@ $^

# objects only need the own .c and .h
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGETS)
