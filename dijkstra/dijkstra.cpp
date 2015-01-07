#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

#include "WeightedGraph.h"

// minCost-vertexID pairs are stored as a Node. 
// Used in PQ for unexplored vertices.
struct Node{
    int ID;
    int cost;
    Node(int i, int c): ID(i), cost(c){}
};

class Dijkstra{
private:
    // PQ in C++ STL is max heap; we'll convert it into min heap
    // by customizing the comparator
    class CompareNode{
    public:
        bool operator()(Node& n1, Node& n2){
            if(n1.cost > n2.cost) return true;
            else                  return false;    
        }
    };

    priority_queue<Node, vector<Node>, CompareNode> unexplored;
    unordered_map<int, int> finalizedCost;

public:
    Dijkstra(WeightedGraph wg, int s){
        // Initialize the finalizedCost hashmap
        for(auto it=wg.begin(); it!=wg.end(); it++){
            // Initialize to be -1(which means unable to reach)
            finalizedCost[ it->first ]=-1;
        }
    }

    void dijkstraSearch(WeightedGraph wg, int s);

};

void WeightedGraph::dijkstraSearch(WeightedGraph wg, int s){
    
}



int main(){
    WeightedGraph wg1("dijkstra_small.txt");
    // WeightedGraph wg1("dijkstra_big.txt");
    wg1.printWeightedGraph();

    return 0;
}