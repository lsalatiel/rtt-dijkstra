all:
	gcc -o main Source/client/main.c Source/libs/src/*.c -g
DijkstraUnitTest:
	gcc -o main Test/DijkstraUnitTest/*.c Source/libs/src/*.c -g
RTTunitTest:
	gcc -o main Test/RTTUnitTest/*.c Source/libs/src/*.c -g