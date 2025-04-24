
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;



int ValueandPath(vector<vector<int>>& triangle, int a, vector<vector<int>>& Paths, int k){
    
    vector<int> C(a,0);
    for (int i = 0; i < a; i++)
    {
        C[i] = triangle[a-1][i];
    }
    
    for (int i = a-2; i > 0; i--)
    {
        for (int j = 0; j <= i; j++) // !
        {
            C[j] = triangle[i][j] + max(C[j],C[j+1]);
        }
        
    }
    return C[0];
}


int main(){

    freopen("5_4 TrianglePath.txt", "r", stdin); 
    int c;
    int a;
    cin >> c;
    
    vector<int> results;
    vector<vector<int>> Paths(c);

    for (int k = 0; k < c; k++)
    {
        cin >> a;
        Paths[k].resize(a);
        vector<vector<int>> triangle(a);
        for (int i = 0; i < a; i++) {
            triangle[i].resize(i + 1);
            for (int j = 0; j <= i; j++) {
                cin >> triangle[i][j];
            }
        }
        results.push_back(ValueandPath(triangle, a, Paths, k));
    }

    for (int result : results) {
        cout << result << endl;
    }
}

