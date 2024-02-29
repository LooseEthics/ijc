CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = main

$TARGET: $OBJS
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)