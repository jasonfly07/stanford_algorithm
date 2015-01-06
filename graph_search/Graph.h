#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph{
private:
    unordered_map<int, unordered_set<int>> adj;

    vector<string> splitString(string s, string delim);
public:
    Graph(){}
    Graph(string fileName);
    void addEdge(int v, int w);
    inline unordered_set<int> getAdj(int v){ return adj[v]; }
    void printGraph();
    Graph transpose();
    inline int V(){ return adj.size(); }

    inline unordered_map<int, unordered_set<int>>::const_iterator begin() const { return adj.begin(); }
    inline unordered_map<int, unordered_set<int>>::const_iterator end()   const { return adj.end();   }
};

Graph::Graph(string fileName){
    ifstream infile;
    infile.open(fileName);

    while(!infile.eof()){
        string str;
        getline(infile, str);
        vector<string> v = splitString(str, " ");
        addEdge(stoi(v[0]),stoi(v[1]));
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

void Graph::addEdge(int v, int w){
    adj[v].insert(w);

    // We have to check if w is already a key; if not, we need to create one for it.
    // The reason is that w might turns out to be a vertex with no outgoing edges.
    auto iterW = adj.find(w);
    if(iterW==adj.end()){
        unordered_set<int> empty;
        adj[w] = empty;
    }
}

void Graph::printGraph(){
    for(auto iter=adj.begin(); iter!=adj.end(); iter++){
        cout << iter->first << ": ";
        for(int i: iter->second){
            cout << i << ",";
        }
        cout << endl;
    }
}

Graph Graph::transpose(){
    Graph gt;
    for(auto iter=adj.begin(); iter!=adj.end(); iter++){
        int v = iter->first;
        for(int w: iter->second){
            gt.addEdge(w,v);
        }
    }
    
    return gt;
}