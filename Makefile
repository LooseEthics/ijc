CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

NON_MAIN_SRCS = bitset.c
SRCS = no-comment.c erat.c
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
erat: erat.o bitset.o
	$(CC) $(CFLAGS) -o $@ $^

erat.exe: erat.o bitset.o
	$(CC) $(CFLAGS) -o $@ $^

# objects only need the own .c and .h
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGETS)
