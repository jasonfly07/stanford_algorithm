// Data structure for (directed) graph
// This is slightly refined from the one in karger_min_cut.cpp.

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

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
    inline vector<int> getAdj(int v){ return adj[v]; }  
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
        cout << currAdj[0] << ": ";
        for(int i=1; i<currAdj.size()-1; i++){
        	cout << currAdj[i] << ",";
        }
        cout << currAdj[currAdj.size()-1] << endl;
    }
}