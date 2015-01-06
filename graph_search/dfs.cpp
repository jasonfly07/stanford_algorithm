#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "Graph.h"

using namespace std;


class DepthFirstSearch{
private:
    unordered_map<int, bool> marked;
    stack<int> dfsStack;
    stack<int> topoStack;
public:
    DepthFirstSearch(Graph g){
        for(auto iter=g.begin(); iter!=g.end(); iter++){
            marked[ iter->first ] = false;
        }
        
        for(auto iter=g.begin(); iter!=g.end(); iter++){
            int currStartV = iter->first;
            if(!marked[currStartV]){
                cout << "Starts from " << currStartV << "." << endl;
                dfs(g, currStartV);
            }
        }
    }
    void dfs(Graph g, int s);
};

void DepthFirstSearch::dfs(Graph g, int s){
    dfsStack.push(s);

    while(!dfsStack.empty()){
        int currV = dfsStack.top();
        dfsStack.pop();
        if(marked[currV]==true){
            cout << currV << " is pushed onto topoStack." << endl;
            topoStack.push(currV);
        }
        else{
            cout << currV << " traversed." << endl;
            marked[currV] = true;

            dfsStack.push(currV);

            for(int w: g.getAdj(currV)){
                if(!marked[w]){
                    dfsStack.push(w);
                }
            }
        }
    }
}

int main(){
    Graph g1("graph_tiny.txt");
    // Graph g1("graph_small.txt");
    // Graph g1("graph_medium.txt");
    // g1.printGraph();
    cout << "There are " << g1.V() << " vertices." << endl;

    

    DepthFirstSearch dfs1(g1);
    
    
    return 0;
}