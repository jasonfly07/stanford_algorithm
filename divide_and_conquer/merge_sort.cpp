// Warming up for count_inversion.cpp

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution{
public:
    void mergeSort(vector<int>& v){
        v = mergeSort_help(v, 0, v.size()-1);
    }

    vector<int> mergeSort_help(vector<int>& v, int i, int j){
        vector<int> output;

        if(i>j) return output;

        if(i==j){
            output.push_back(v[i]);
            return output;
        }

        else{
            int mid = (i+j)/2;
            vector<int> sortedL = mergeSort_help(v, i, mid);
            vector<int> sortedR = mergeSort_help(v, mid+1, j);

            if(sortedR.size()==0) return sortedL;
            if(sortedL.size()==0) return sortedR;

            int iterL = 0;
            int iterR = 0;
            int minL, minR;

            while(iterL<sortedL.size() || iterR<sortedR.size()){
                if(iterL<sortedL.size()) minL = sortedL[iterL];
                else                     minL = numeric_limits<int>::max();
                if(iterR<sortedR.size()) minR = sortedR[iterR];
                else                     minR = numeric_limits<int>::max();

                if(minL < minR){
                    output.push_back(minL);
                    iterL++;
                }
                else{
                    output.push_back(minR);
                    iterR++;
                }
            }

            return output;
        }

    }

    void printVector(vector<int>& v){
        for(int i: v){
            cout << i << ",";
        }
        cout << endl;
    }

};


int main(){

    Solution s1;
    vector<int> v{1};
    s1.mergeSort(v);
    s1.printVector(v);

    return 0;
}