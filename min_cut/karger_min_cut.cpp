// Karger's "random contraction" algorithm for computing minimum cut of an undirected graph.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
using namespace std;


// Store the graph in a list of adjacency lists
class Graph{
private:
    vector<vector<int>> adj;
public:
    Graph(){}
    Graph(string fileName);
    Graph(const Graph& anotherG);
    vector<string> splitString(string s, string delim);
    void printGraph();
    inline int V(){ return adj.size(); }

    int computeKargerOnce();
    int computeKarger();
};

Graph::Graph(string fileName){
    ifstream infile;
    infile.open(fileName);

    while(!infile.eof()){
        string str;
        getline(infile, str);

        vector<string> v = splitString(str, " ");
        vector<int> currAdj;
        for(string s:v){
            if(s.size()>0) currAdj.push_back( stoi(s) );
        }
        adj.push_back(currAdj);
    }
}

// Copy from another graph
Graph::Graph(const Graph& anotherG){
    for(auto currAdj: anotherG.adj){
        vector<int> newAdj;
        for(int i: currAdj){
            newAdj.push_back(i);
        }
        adj.push_back(newAdj);
    }
}

vector<string> Graph::splitString(string s, string delim){
    vector<string> allSubStr;
    auto start = 0U;
    auto end = s.find(delim);
    
    while (end != string::npos){
        allSubStr.push_back( s.substr(start, end - start) );
        // cout << s.substr(start, end - start) << endl;
        start = end + delim.length();
        end = s.find(delim, start);
    }
    allSubStr.push_back( s.substr(start, end) );
    // cout << s.substr(start, end);

    return allSubStr;
}

void Graph::printGraph(){
    for(auto currAdj: adj){
        for(auto i: currAdj){
            cout << i << ",";
        }
        cout << endl;
    }
}

int Graph::computeKargerOnce(){
    // 0. Make a copy of the original graph
    //    All subsequent operations will be applied to this copy
    Graph g = *this;

    while(g.adj.size()>2){
        // cout << "loop starts" << endl;
        // g.printGraph();
        // cout << endl;

        // 1. Pick a random vertex vA and its neighbor vB.
        //    By default, vA is the one to be kept, while vB will be "swollen" by vA.
        //    A few notes on the confusing variables:
        //    1a. indA & indB are simply 2 random numbers for picking vA & vB
        //    1b.   vA &   vB are the actual vertex ID.
        //    1c. After generating vA & vB, indB will be used to store the location of 
        //        adjacency list B. (indA already served this purpose.)
        int indA = rand()%g.V();
        int indB = rand()%(g.adj[indA].size()-1)+1;
        int vA = g.adj[indA][0];
        int vB = g.adj[indA][indB];
        
        for(int i=0; i<g.adj.size(); i++){
            if(g.adj[i][0]==vB){
                indB = i;
                break;
            }
        }

        // cout << "vA: " << vA << endl; 
        // cout << "vB: " << vB << endl << endl;

        // 2. Remove vB from vA's adjacency list
        g.adj[indA].erase(remove(g.adj[indA].begin(), g.adj[indA].end(), vB), g.adj[indA].end());

        // 3. Remove vA from vB's adjacency list
        g.adj[indB].erase(remove(g.adj[indB].begin(), g.adj[indB].end(), vA), g.adj[indB].end());

        // 4. vA will take over all of vB's adjacent vertices (is there a better way to concatenate?)
        for(int i=1; i<g.adj[indB].size(); i++){
            g.adj[indA].push_back( g.adj[indB][i] );
        }
        
        // 5. Go through all of vA's adjacent vertices and visit their respective adjacent list.
        //    Replace all vB in these lists with vA.
        for(int i=1; i<g.adj[indA].size(); i++){

            // First, we have to find out where this list is
            int currAdjInd = 0;
            for(int j=0; j<g.adj.size(); j++){
                if(g.adj[indA][i] == g.adj[j][0]){
                    currAdjInd = j;
                    break;
                }
            }
            // After we locate the list, replace all vB with vA
            replace(g.adj[currAdjInd].begin()+1, g.adj[currAdjInd].end(), vB, vA);
        }

        // 6. Finally, erase vB's adjacency list.
        g.adj.erase(g.adj.begin()+indB);

        // g.printGraph();
        // cout << endl;

    }



    return g.adj[0].size()-1;
}

int Graph::computeKarger(){
    int n = V();
    int iterations = static_cast<int>( n*(n-1)*0.5*log(n) );
    int bestMin = numeric_limits<int>::max();

    for(int i=0; i<iterations; i++){
        int currMin = computeKargerOnce();
        if(currMin < bestMin) bestMin = currMin;
        cout << i << ": " << currMin << endl;
    }

    return bestMin;
}


int main(){

    srand(time(NULL));
    
    Graph g1("karger_big.txt");

    cout << "min cut: " << g1.computeKarger() << endl;


    

    return 0;
}