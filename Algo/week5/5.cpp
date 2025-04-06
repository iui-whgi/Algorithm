#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

void ValueandPath(vector<vector<int>>& triangle, int a, vector<int>& path, int& maxSum) {
    vector<vector<int>> dp(a, vector<int>(a, 0));
    
    for (int i = 0; i < a; i++) {
        dp[a-1][i] = triangle[a-1][i];
    }
    
    for (int i = a-2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j] + max(dp[i+1][j], dp[i+1][j+1]);
        }
    }
    
    maxSum = dp[0][0];
    
    int j = 0;
    path[0] = triangle[0][0];
    
    for (int i = 0; i < a-1; i++) {
        if (dp[i+1][j+1] >= dp[i+1][j]) {
            j = j + 1;
        }
        path[i+1] = triangle[i+1][j];
    }
}


int main() {
    int c;
    cin >> c;
    
    vector<int> results(c);
    vector<vector<int>> paths(c);
    
    for (int k = 0; k < c; k++) {
        int a;
        cin >> a;
        
        vector<vector<int>> triangle(a);
        for (int i = 0; i < a; i++) {
            triangle[i].resize(i + 1);
            for (int j = 0; j <= i; j++) {   // ! 여기서 갈림
                cin >> triangle[i][j];
            }
        }
        
        paths[k].resize(a);
        
        int maxSum;
        ValueandPath(triangle, a, paths[k], maxSum);
        results[k] = maxSum;
    }
    
    for (int k = 0; k < c; k++) {
        cout << results[k] << endl;
        
        cout << paths[k][0];
        for (int i = 1; i < paths[k].size(); i++) {
            cout << " " << paths[k][i];
        }
        cout << endl;
    }
    
    return 0;
}