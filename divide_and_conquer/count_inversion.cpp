// Count the number of inverted pairs in an unsorted array.
// This is done via a slightly modified mergeSort (in fact, only 2 new lines are added.) 

#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
using namespace std;

class Solution{
public:
    double invCount; // Stores the total number of inverted pairs

    void countInversion(vector<int>& v){
        invCount = 0;
        v = countInversion_help(v, 0, v.size()-1);
    }

    vector<int> countInversion_help(vector<int>& v, int i, int j){
        vector<int> output;

        if(i>j) return output;

        if(i==j){
            output.push_back(v[i]);
            return output;
        }

        else{
            int mid = (i+j)/2;
            vector<int> sortedL = countInversion_help(v, i, mid);
            vector<int> sortedR = countInversion_help(v, mid+1, j);

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

                    // Every time an item from the right sorted array is pushed,
                    // we count the number of items from the left and add it to 
                    // the total count of inversions.
                    invCount += (sortedL.size()-iterL);
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
    // vector<int> v{1,3,7,6,5,4,2,8};

    vector<int> v;
    ifstream infile;
    string str;
    infile.open("inversion.txt");
    while(!infile.eof()){
        getline(infile, str);
        v.push_back( stoi(str) );
    }


    // s1.printVector(v);
    s1.countInversion(v);
    cout << fixed;
    cout << "There are " << s1.invCount << " inversions." << endl;

    return 0;
}