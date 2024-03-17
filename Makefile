CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

SRCS = bitset.c no-comment.c
OBJS = $(SRCS:.c=.o)
ifeq ($(OS),Windows_NT)
	TARGETS = $(SRCS:.c=.exe)
	RM = del /Q
else
	TARGETS = $(SRCS:.c=)
	RM = rm -f
endif

all: $(TARGETS)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.exe: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGETS)
