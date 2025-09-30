UNAME_S := $(shell uname -s)
CC = gcc
LD = gcc
CFLAGS = -ggdb -Wall -std=c99
LDFLAGS =

BIT_OPS_OBJS = bit_ops.o test_bit_ops.o
BIT_OPS_PROG = bit_ops

LFSR_OBJS = lfsr.o test_lfsr.o
LFSR_PROG = lfsr

VECTOR_OBJS = vector.o vector-test.o
VECTOR_PROG = vector-test

BINARIES = $(VECTOR_PROG) $(BIT_OPS_PROG) $(LFSR_PROG)

.PHONY: all clean

all: $(BINARIES)

$(BIT_OPS_PROG): $(BIT_OPS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(LFSR_PROG): $(LFSR_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(VECTOR_PROG): $(VECTOR_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Header dependencies
bit_ops.c test_bit_ops.c: bit_ops.h
lfsr.c test_lfsr.c: lfsr.h
vector.c vector-test.c: vector.h

# Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(BINARIES) *.dSYM