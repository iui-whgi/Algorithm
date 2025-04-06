
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;



int pathAlgo(vector<vector<int>>& triangle, int a){
    vector<int> Array(a,0);
    
    Array = triangle[a];
    
    int C = a;

    for (int i = a-2; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            triangle[i][j] = triangle[i][j] + max(triangle[i+1][j],triangle[i+1][j+1]);
        }   
    }

    return triangle[0][0];
}

int main(){
    int c;

    int a;
    cin >> c;
    // vector<vector<int>> triangle(c, vector<int>(c,0));
    
    vector<int> results;
    for (int k = 0; k < c; k++)
    {
        cin >> a;
        vector<vector<int>> triangle(a);
        for (int i = 0; i < a; i++) {
            triangle[i].resize(i + 1);
            for (int j = 0; j <= i; j++) {
                cin >> triangle[i][j];
            }
        }
        results.push_back(pathAlgo(triangle, a));

    }

    for (int result : results) {
        cout << result << endl;
    }
}