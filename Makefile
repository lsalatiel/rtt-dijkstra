CC = gcc
override CFLAGS += -Wall -Wextra -O3 -g -lm
MAIN = trab2
EXEC = Source/client/main.c Source/libs/src/*.c

all:
	$(CC) $(CFLAGS) -o $(MAIN) $(EXEC) 
clean:
	rm -rf $(MAIN)
