#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
using namespace std;

class WeightedGraph{
private:
    unordered_map<int, unordered_map<int, int>> adj;

    vector<string> splitString(string s, string delim);
public:
    WeightedGraph(){}
    WeightedGraph(string fileName);
    void addEdge(int v, int w, int cost);
    inline unordered_map<int, int> getAdj(int v){ return adj[v]; }
    void printWeightedGraph();
    inline int V(){ return adj.size(); }

    inline unordered_map<int, unordered_map<int, int>>::const_iterator begin() const { return adj.begin(); }
    inline unordered_map<int, unordered_map<int, int>>::const_iterator end()   const { return adj.end();   }
};

WeightedGraph::WeightedGraph(string fileName){
    ifstream infile;
    infile.open(fileName);

    while(!infile.eof()){
        string str;
        getline(infile, str);
        vector<string> v = splitString(str, " ");

        int from = stoi(v[0]);
        for(int i=1; i<v.size(); i++){
            // Silly hack to get rid of carriage return character 
            if(v[i].size()==1 && v[i][0]==13) continue;
            
            if(v[i].size()!=0){
                vector<string> pair = splitString(v[i], ",");
                int to = stoi(pair[0]);
                int cost = stoi(pair[1]);
                addEdge(from, to, cost);
            }
        }
    }
}

vector<string> WeightedGraph::splitString(string s, string delim){
    vector<string> allSubStr;
    auto start = 0U;
    auto end = s.find(delim);
    
    while (end != string::npos){
        allSubStr.push_back( s.substr(start, end - start) );
        start = end + delim.length();
        end = s.find(delim, start);
    }
    allSubStr.push_back( s.substr(start, end) );

    return allSubStr;
}

void WeightedGraph::addEdge(int v, int w, int cost){
    adj[v][w] = cost;

    // We have to check if w is already a key; if not, we need to create one for it.
    // The reason is that w might turns out to be a vertex with no outgoing edges.
    auto iterW = adj.find(w);
    if(iterW==adj.end()){
        unordered_map<int, int> empty;
        adj[w] = empty;
    }
}

void WeightedGraph::printWeightedGraph(){
    cout << "The graph is: " << endl;
    for(auto iter1=adj.begin(); iter1!=adj.end(); iter1++){
        cout << iter1->first << ": ";
        for(auto iter2=(iter1->second).begin(); iter2!=(iter1->second).end(); iter2++){
            cout << iter2->first << "(" << iter2->second << ")" << ",";
        }
        cout << endl;
    }
}