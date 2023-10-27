all:
	gcc -o main Source/client/main.c Source/libs/src/*.c -g
DijkstraTest:
	gcc -o main Test/DijkstraTest/*.c Source/libs/src/*.c -g
RTTTest:
	gcc -o main Test/RTTtest/*.c Source/libs/src/*.c -g