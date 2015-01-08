#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>

using namespace std;

class RollingMedian{
private:
    class Compare{
    public:
        bool operator()(int n1, int n2){
            if(n1 > n2) return true;
            else        return false;    
        }
    };

    vector<int> rollingInput;
    vector<int> allMedian;
    priority_queue<int>                       maxPQ;
    priority_queue<int, vector<int>, Compare> minPQ;

public:
    RollingMedian(string fileName){
        readInput(fileName);
        processRollingMedian();
    }

    void processRollingMedian();

    void readInput(string fileName);
    void printMedian(){
        for(int m: allMedian) cout << m << ",";
        cout << endl;
    }

    int computeMedianSum(){
        int sum = 0;
        for(int i: allMedian) sum += i;
        return sum;
    }

};

void RollingMedian::readInput(string fileName){
    ifstream infile;
    infile.open(fileName);

    while(!infile.eof()){
        string str;
        getline(infile, str);
        rollingInput.push_back( stoi(str) );
    }
}

void RollingMedian::processRollingMedian(){
    // Handle the first 2 inputs
    int head_small = min(rollingInput[0], rollingInput[1]);
    int head_big   = max(rollingInput[0], rollingInput[1]);

    minPQ.push(head_big);
    maxPQ.push(head_small);

    allMedian.push_back( rollingInput[0] );
    allMedian.push_back( head_small );

    int currMedian = allMedian[1];

    // Now we process the incoming numbers one-by-one
    for(int i=2; i!=rollingInput.size(); i++){
        // cout << maxPQ.top() << ", " << minPQ.top() << endl;
        int currNum = rollingInput[i];

        // See which heap currNum should go to
        if(currNum > currMedian) minPQ.push(currNum);
        else                     maxPQ.push(currNum);

        // If the sizes of the 2 heaps differ more than 1, we have to balance it
        if(minPQ.size() > maxPQ.size()+1){
            int rightMin = minPQ.top();
            minPQ.pop();
            maxPQ.push(rightMin);
        }
        else if(maxPQ.size() > minPQ.size()+1){
            int leftMax = maxPQ.top();
            maxPQ.pop();
            minPQ.push(leftMax);
        }

        // Now we can compute the median swiftly
        if(minPQ.size()-maxPQ.size()==1){
            currMedian = minPQ.top();
        }
        else if(maxPQ.size()-minPQ.size()==1){
            currMedian = maxPQ.top();
        }
        else{// if maxPQ.size()==minPQ.size()
            currMedian = maxPQ.top();
        }   

        allMedian.push_back(currMedian);
    }
}

int main(){
    // RollingMedian rm1("median_small.txt");
    RollingMedian rm1("median_big.txt");

    // rm1.printMedian();

    cout << rm1.computeMedianSum()%10000 << endl;


    return 0;
}