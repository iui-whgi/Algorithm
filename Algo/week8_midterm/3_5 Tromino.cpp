
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
int cnt = 1;



void tromino(int n , Matrix& A, int srow, int scol , int r, int c){
    
    
}


int main(){
    int N, r, c;
    cin >> N >> r >> c;

    int srow, scol;

    Matrix arr(N, vector<int>(N,-1));
    arr[r][c] = 0;
    tromino(N, arr, srow, scol, r, c);
    



    return 0;    
}

