CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -O2 -fsigned-char -fwrapv

.PHONY: all run clean

all: informatics_lr1

informatics_lr1: main.c
	$(CC) $(CFLAGS) main.c -o informatics_lr1

run: informatics_lr1
	./informatics_lr1

clean:
	$(RM) informatics_lr1
