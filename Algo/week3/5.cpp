
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
int cnt = 1;


int whereis(int m, int srow, int scol, int row, int col){
    int midRow = srow + m;
    int midCol = scol + m;

    if(midRow  <= row){
        if(midCol  <= col) return 4;
        else return 3;
    }
    else{
        if(midCol <= col) return 2;
        else return 1;
    }
}

// int whereis(int m, int srow, int scol, int row, int col) {
//     int midRow = srow + m;
//     int midCol = scol + m;
    
//     if (row < midRow) {
//         if (col < midCol) return 1; // Top-left
//         else return 2;              // Top-right
//     } else {
//         if (col < midCol) return 3; // Bottom-left
//         else return 4;              // Bottom-right
//     }
// }

void fill(int where, Matrix& A,int srow, int scol){
    if(where != 1) A[srow][scol] = cnt;
    if(where != 2) A[srow][scol+1] = cnt;
    if(where != 3) A[srow+1][scol] = cnt;
    if(where != 4) A[srow+1][scol+1] = cnt;
    cnt++;
    return;
}

pair<int, int> hole(int subQuadrant, int quadrant, int mid, int srow, int scol, int row, int col) {
    if (subQuadrant == quadrant) {
        // If this is the quadrant with the original hole, pass it down
        return {row, col};
    } else {
        // Otherwise, the hole is where we placed our tromino
        if (subQuadrant == 1) return {srow + mid - 1, scol + mid - 1}; // Top-left
        if (subQuadrant == 2) return {srow + mid - 1, scol + mid};     // Top-right
        if (subQuadrant == 3) return {srow + mid, scol + mid - 1};     // Bottom-left
        if (subQuadrant == 4) return {srow + mid, scol + mid};         // Bottom-right
    }
    return {-1, -1}; // Should never happen
}

void tromino(int n, Matrix& A, int srow,int scol, int row, int col){ 
    int m = n/2;
    int where;
    int hrow, hcol;
    where = whereis(m, srow, scol, row , col );
    // cout << where << endl;
    if(n==2)
        fill(where, A, srow, scol);
    else{
        fill(where, A, srow + m - 1, scol + m - 1);
        pair<int, int> hole1 = hole(1,where, m , srow, scol, row, col);
        tromino(m, A, srow, scol, hole1.first, hole1.second);

        pair<int, int> hole2 = hole(2,where, m , srow, scol, row, col);
        tromino(m, A, srow, scol+m, hole2.first, hole2.second);

        pair<int, int> hole3 = hole(3,where, m , srow, scol, row, col);
        tromino(m, A, srow+m, scol, hole3.first, hole3.second);
        
        pair<int, int> hole4 = hole(4,where, m , srow, scol, row, col);
        tromino(m, A, srow+m, scol+m, hole4.first, hole4.second);
        
        
    }
}

int main(){
    int N, r, c;
    cin >> N >> r >> c;

    Matrix A(N, vector<int>(N, -1));

    A[r][c] = 0;

    tromino(N, A, 0 , 0 ,r, c);
    
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         cout << A[i][j] << " ";
    //     }
    //     cout << endl;
        
    // }
    for (int i = 0; i < N; i++) {
        cout << (A[i][0] == -1 ? 0 : A[i][0]);
        for (int j = 1; j < N; j++) {
            cout << " " << (A[i][j] == -1 ? 0 : A[i][j]); // Print 0 for the original hole
        }
        cout << endl;
    }
    
    return 0;

    

}