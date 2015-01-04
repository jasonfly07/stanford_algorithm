#include <iostream>
#include <vector>

#include "Graph.h"

using namespace std;

class DepthFirstSearch{
private:
    vector<bool> marked;
public:
    DepthFirstSearch(Graph g, int s){
        count = 0;
        marked = vector<bool>(g.V(), false);
        dfs(g, s);
    }
    void dfs(Graph g, int s);
};

void DepthFirstSearch::dfs(Graph g, int s){
    cout << s << " traversed." << endl;
    marked[s] = true;
    for(int v: g.getAdj(s)){
        if(!marked[v]) dfs(g, v);
    }
}


int main(){
    Graph g1("graph_small.txt");
    g1.printGraph();

    DepthFirstSearch dfs1(g1, 6);

    return 0;
}