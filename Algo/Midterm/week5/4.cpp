
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;


int ValueandPath(vector<vector<int>>& triangle, int a, vector<vector<int>>& Paths, int k){
    
    vector<int> C(a,0);
    for (int i = 0; i < a; i++)
    {
        C[i] = triangle[a-1][i];
    }  // ! triangle 마지막 줄로 초기화 중

    
    for (int i = a-2; i >= 0; i--) // ! 0 base 이기도 하고  마지막 다음줄을 만들어 나가는 과정이니까
    {
        for (int j = 0; j <= i; j++)
        {
            C[j] = triangle[i][j] + max(C[j],C[j+1]);
        }   
    }
    
    return C[0];
}



int main(){
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

