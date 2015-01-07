#include <iostream>
using namespace std;

#include "WeightedGraph.h"

int main(){
    WeightedGraph wg1("dijkstra_small.txt");
    // WeightedGraph wg1("dijkstra_big.txt");
    wg1.printWeightedGraph();

    return 0;
}