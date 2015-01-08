// Dijkstra's single shortest path algorithm.
// Beware: Dijsktra's algorithm requires a heap sturcture that supports
// both retrieving the min item AND find a particular item, 
// and priority_queue in STL does not support the latter operation.
// It is recommended to use "set", which supports both.

// Another trick (which is used in the following code), is to NOT find & update.
// This is best explained by Googol from Stack Overflow:

// "priority_queue in C++ (or PriorityQueue in Java) do not provide a decrease-key operation, 
// as said previously. A nice trick for using those classes when implementing Dijkstra is using 
// "lazy deletion". The main loop of Dijkstra algorithm extracts the next node to be processed from 
// the priority queue, and analises all its adjacent nodes, eventually changing the cost of the 
// minimal path for a node in the priority queue. This is the point where decrease-key is usually 
// needed in order to update the value of that node.

// "The trick is not change it at all. Instead, a "new copy" for that node (with its new better cost) 
// is added into the priority queue. Having a lower cost, that new copy of the node will be extracted 
// before the original copy in the queue, so it will be processed earlier.

// "The problem with this "lazy deletion" is that the second copy of the node, with the higher 
// bad cost, will be eventually extracted from the priority queue. But that will be always occur after 
// the second added copy, with a better cost, has being processed. So the very first thing that the 
// main Dijkstra loop must do when extracting the next node from the priority queue is checking if 
// the node has being previously visited (and we know the shortest path already). It is in that 
// precise moment when we will be doing the "lazy deletion" and the element must be simply ignored.

// "This solution will have a cost both in memory and time, because the priority queue is storing 
// "dead elements" that we have not removed. But the real cost will be quite small, and programming 
// this solution is, IMHO, easier than any other alternative that tries to simulate the missing 
// decrease-key operation.""

#include <iostream>
#include <queue>
#include <limits>
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

    priority_queue<Node, vector<Node>, CompareNode> candidatePool;
    unordered_map<int, int> finalizedCost;
    unordered_map<int, bool> finalized;

public:
    Dijkstra(WeightedGraph wg, int s){
        // Initialize the finalizedCost hashmap
        for(auto it=wg.begin(); it!=wg.end(); it++){

            // Initialize all of them to be -1 firstly (which means unable to reach)
            finalizedCost[ it->first ] = -1;
            finalized[ it->first ] = false;
        }

        // Push the starting vertex in PQ
        candidatePool.push( Node(s, 0) );

        // Start the central Dijkstra while loop routine
        dijkstraSearch(wg, s);

    }

    void dijkstraSearch(WeightedGraph wg, int s);
    void printFinalizedCost();
};

void Dijkstra::dijkstraSearch(WeightedGraph wg, int s){

    // while-loop until all the items in PQ is cleared
    while(!candidatePool.empty()){
        Node v = candidatePool.top();
        candidatePool.pop();

        // Because we use the "lazy deletion" trick, we have to inspect whether this
        // Node has been finalized. If yes, ignore it. 
        if(finalized[v.ID]) continue;
        else{
            cout << v.ID << " is finalized." << endl;
            finalizedCost[v.ID] = v.cost;
            finalized[v.ID] = true;
        }
        

        unordered_map<int, int> currList = wg.getAdj(v.ID);

        for(auto it=currList.begin(); it!=currList.end(); it++){
            int w = it->first;
            int vw_cost = it->second;
            cout << "w: " << w << ", " << "vw_cost: " << vw_cost << endl; 
            cout << "Pushed " << w << "(" << v.cost+vw_cost << ") in PQ." << endl;
            // Instead of checking whether this new cost is better or worse than the
            // one already in PQ, we push it in PQ anyway.
            // PQ will sort it for us, and pop the best one when we need it.
            candidatePool.push( Node(w, v.cost+vw_cost) );
        }
    }
}

void Dijkstra::printFinalizedCost(){
    for(auto it=finalizedCost.begin(); it!=finalizedCost.end(); it++){
        cout << "To reach " << it->first << ", the cost is " << it->second << endl;
    }
}



int main(){
    // WeightedGraph wg1("dijkstra_small.txt");
    WeightedGraph wg1("dijkstra_big.txt");
    wg1.printWeightedGraph();

    Dijkstra dijk(wg1, 1);
    dijk.printFinalizedCost();


    return 0;
}