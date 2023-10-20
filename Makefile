all:
	gcc -o main Source/client/main.c Source/libs/src/*.c -g
testUnitDijkstra:
	gcc -o main Test/DijkstraUnitTest/*.c Source/libs/src/*.c -g