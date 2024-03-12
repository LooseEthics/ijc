CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

SRCS = main.c
OBJS = $(SRCS:.c=.o)
ifeq ($(OS),Windows_NT)
	TARGET = main.exe
else
	TARGET = main
endif

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del $(OBJS) $(TARGET)
else
	rm -f $(OBJS) $(TARGET)
endif
