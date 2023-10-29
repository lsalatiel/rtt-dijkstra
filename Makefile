CC = gcc
override CFLAGS += -Wall -Wextra -g -lm
MAIN = main
EXEC = Source/client/main.c Source/libs/src/*.c
EXEC_DIJKSTRA_TEST = Test/DijkstraTest/*.c Source/libs/src/*.c
EXEC_RTT_TEST = Test/RTTtest/*.c Source/libs/src/*.c

all:
	$(CC) $(CFLAGS) -o $(MAIN) $(EXEC) 
DijkstraTest:
	$(CC) $(CFLAGS) -o $(MAIN) $(EXEC_DIJKSTRA_TEST)
RTTTest:
	$(CC) $(CFLAGS) -o $(MAIN) $(EXEC_RTT_TEST)
clean:
	rm -rf $(MAIN)
