// Kosaraju-Sharir's two-pass algorithm for finding strong connected components(SCC)
// of a directly graph.
// This algorithm is closely related to topological sorting, since finding SCC in a graph
// is kindof like finding topological sorting of its SCCs.

// Note: the current version is buggy.
// (It can pass the huge case, but will fail at some smaller ones.)
// TODO: fix it.

#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>

#include "Graph.h"

using namespace std;


class KosarajuSCC{
private:
    unordered_map<int, bool> marked;
    stack<int> dfsStack;
    stack<int> firstStack;
    vector<int> firstResult;
    vector<unordered_set<int>> SCC;

    void firstPass(Graph g);
    void secondPass(Graph g);
public:
    KosarajuSCC(Graph g){
        Graph gt = g.transpose();

        // cout << "KosarajuSCC starts." << endl;
        for(auto iter=g.begin(); iter!=g.end(); iter++){
            marked[ iter->first ] = false;
        }
        firstPass(gt);
        

        for(auto iter=g.begin(); iter!=g.end(); iter++){
            marked[ iter->first ] = false;
        }
        secondPass(g);
    }

    void printSCC();
    void printSCCSize(); // Temporary function for assignment 4
    void printFirstResult(){
        cout << "Running time: ";
        for(int i: firstResult){
            cout << i << ",";
        }
        cout << endl;
    }
    inline int numSCC(){ return SCC.size(); }
};

void KosarajuSCC::firstPass(Graph g){
    for(auto iter=g.begin(); iter!=g.end(); iter++){
        int s = iter->first;

        if(!marked[s]){
            dfsStack.push(s);
            while(!dfsStack.empty()){
                int currV = dfsStack.top();
                dfsStack.pop();
                if(marked[currV]==true){
                    cout << currV << " is pushed onto firstStack." << endl;
                    firstStack.push(currV);
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
    }

    while(!firstStack.empty()){
        firstResult.push_back( firstStack.top() );
        firstStack.pop();
    }
}

void KosarajuSCC::secondPass(Graph g){
    for(int s: firstResult){
        if(!marked[s]){
            unordered_set<int> currSCC;

            dfsStack.push(s);
            while(!dfsStack.empty()){
                int currV = dfsStack.top();
                dfsStack.pop();
                if(marked[currV]==true){
                    // cout << currV << " is pushed onto firstStack." << endl;
                    // firstStack.push(currV);
                }
                else{
                    cout << currV << " traversed." << endl;
                    currSCC.insert(currV);
                    marked[currV] = true;

                    dfsStack.push(currV);

                    for(int w: g.getAdj(currV)){
                        if(!marked[w]){
                            dfsStack.push(w);
                        }
                    }
                }
            }

            SCC.push_back(currSCC);
        }
    }
}

void KosarajuSCC::printSCC(){
    for(auto currSCC: SCC){
        for(int i: currSCC){
            cout << i << ",";
        }
        cout << endl;
    }
}

void KosarajuSCC::printSCCSize(){
    cout << "SCC sizes are: ";
    priority_queue<int> allSize;

    for(auto currSCC: SCC){
        allSize.push(currSCC.size());
    }

    stack<int> allSizeReversed;
    while(!allSize.empty()){
        allSizeReversed.push( allSize.top() );
        // cout << allSize.top() << ",";
        allSize.pop();
    }

    while(!allSizeReversed.empty()){
        cout << allSizeReversed.top() << ",";
        allSizeReversed.pop();
    }

    cout << endl;
}


int main(){
    Graph g1("graph_tiny.txt");
    // Graph g1("graph_small.txt");
    // Graph g1("graph_medium.txt");
    // Graph g1("graph_huge.txt");

    cout << "There are " << g1.V() << " vertices." << endl;
    
    // g1.printGraph();

    KosarajuSCC kscc1(g1);
    // kscc1.printFirstResult();
    // kscc1.printSCC();
    kscc1.printSCCSize();

    cout << "There are " << kscc1.numSCC() << " SCCs." << endl;

    return 0;
}