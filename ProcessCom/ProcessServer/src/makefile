

SRCFILE=$(wildcard *.c)
DFILE=$(patsubst %.c,%.o,$(SRCFILE))
TARGET=PipeServer.out
CC=gcc
INCPATH=../inc
CFLAGS=-I$(INCPATH) -c -g -Wall

$(TARGET):$(DFILE)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $^ $(CFLAGS)

.PHONY:
clean:
	rm -f $(DFILE)
