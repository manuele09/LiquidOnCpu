# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Output binary name
BIN = main

# Source files
SRCS = $(wildcard *.c)

# Header files
HDRS = $(wildcard *.h)

# Object files
OBJS = $(SRCS:.c=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BIN)

.PHONY: all clean
