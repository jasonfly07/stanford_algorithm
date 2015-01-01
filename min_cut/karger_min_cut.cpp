#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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
    // g.printGraph();

    // 1. Pick a random vertex vA and its neighbor vB.
    //    By default, vA is the one to be kept, while vB will be "swollen"
    //    A few notes on the confusing variables:
    //    1a. indA & indB are simply 2 random numbers for picking vA & vB
    //    1b.   vA &   vB are the actual vertex ID.
    //    1c. After generating vA & vB, indB will be used to store the location of 
    //        adjacency list B. (indA already served this purpose.)
    int indA = rand()%V();
    int indB = rand()%(adj[indA].size()-1)+1;
    int vA = adj[indA][0];
    int vB = adj[indA][indB];
    for(int i=0; i<adj.size(); i++){
        if(adj[i][0]==vB){
            indB = i;
            break;
        }
    }

    cout << vA << "," << vB << endl;
    cout << indA << "," << indB << endl;

    // 2. Remove vB from vA's adjacency list
    // v.erase(remove(v.begin(), v.end(), 99), v.end());

    // 3. Remove vA from vB's adjacency list



    return 0;
}


int main(){

    srand(time(NULL));
    
    Graph g1("karger_small.txt");

    g1.computeKargerOnce();



    

    return 0;
}