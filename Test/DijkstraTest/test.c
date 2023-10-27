#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Source/libs/libs/graph.h"
#include "../../Source/libs/libs/utils.h"

int main(int argc, char** argv){
    Graph* g = graph_construct(5);
    graph_add_directed_edge(g, 0, 1, 10.0);
    graph_add_directed_edge(g, 0, 2, 3.0);
    graph_add_directed_edge(g, 1, 2, 1.0);
    graph_add_directed_edge(g, 2, 1, 4.0);
    graph_add_directed_edge(g, 1, 3, 2.0);
    graph_add_directed_edge(g, 2, 4, 2.0);
    graph_add_directed_edge(g, 3, 4, 7.0);
    graph_add_directed_edge(g, 2, 3, 8.0);
    graph_add_directed_edge(g, 4, 3, 9.0);
    
    //int* dijkstra = dijkstra_algorithm(g, 0, 0); // correct: 0 -1 -1 -1 -1 ||| Output: 0 -1 -1 -1 -1  [CORRECT] ||| Cost: CORRECT
    //int* dijkstra = dijkstra_algorithm(g, 0, 1); // correct: 0 2 1 -1 -1   ||| Output: 0 2 4 1 -1     [ERROR]   ||| Cost: CORRECT
    //int* dijkstra = dijkstra_algorithm(g, 0, 2); // correct: 0 2 -1 -1 -1  ||| Output: 0 2 -1 -1 -1   [CORRECT] ||| Cost: CORRECT
    //int* dijkstra = dijkstra_algorithm(g, 0, 3); // correct: 0 2 1 3 -1    ||| Output: 0 2 4 1 3      [ERROR]   ||| Cost: CORRECT
    int* dijkstra = dijkstra_algorithm(g, 0, 4); // correct: 0 2 4 -1 -1   ||| Output: 0 2 4 -1 -1    [CORRECT] ||| Cost: CORRECT
    
    for(int i = 0; i < 5; i++){
        printf("%d ", dijkstra[i]);
    }
    printf("\n cost: %lf\n", dijkstra_algorithm_cost(g, 0, 4));

    return 0;
}