
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
int cnt = 1;

int wherishole(int n, Matrix& A, int srow, int scol, int r, int c){
    int midRow = srow + n/2;
    int midCol = scol + n/2;

    if (r < midRow) {
        return (c < midCol) ? 1 : 2;
    } else {
        return (c < midCol) ? 3 : 4;
    }
}


void fill(int where, Matrix& A, int srow, int scol){ // srow , scol은 중앙을 기준으 말함함

    if(where != 1) A[srow][scol] = cnt;
    if(where != 2) A[srow][scol+1] = cnt;
    if(where != 3) A[srow+1][scol] = cnt;
    if(where != 4) A[srow+1][scol+1] = cnt;
    cnt++;

}

pair<int,int> findhole(int plane, int where, Matrix& A, int srow, int scol , int row, int col ,int mid){

    
    if(plane == where) return {row,col};
    else{
        if(plane == 1) return {srow+mid-1, scol+mid-1};
        if(plane == 2) return {srow+mid-1, scol+mid};
        if(plane == 3) return {srow+mid, scol+mid-1};
        if(plane == 4) return {srow+mid, scol+mid};
    }


    

}


void tromino(int n , Matrix& A, int srow, int scol , int row, int col){

    int mid = n/2;
    int where = wherishole(n, A, srow, scol, row, col);

    if(n==2){
        fill(where, A, srow, scol);
    }
    else{
        fill(where, A, srow + mid - 1, scol + mid - 1);


        pair<int,int> hole1 = findhole(1,where, A, srow , scol, row, col, n/2);
        tromino(n/2, A, srow, scol, hole1.first, hole1.second);
        
        pair<int,int> hole2 = findhole(2,where, A, srow, scol, row, col, n/2);
        tromino(n/2, A, srow, scol+mid, hole2.first, hole2.second);
        
        pair<int,int> hole3 = findhole(3,where, A, srow, scol, row, col, n/2);
        tromino(n/2, A, srow+mid, scol, hole3.first, hole3.second);
        
        pair<int,int> hole4 = findhole(4,where, A, srow, scol, row, col, n/2);
        tromino(n/2, A, srow+mid, scol+mid, hole4.first, hole4.second);
        

    }

    
    
}


int main(){
    int N, r, c;
    cin >> N >> r >> c;

    int srow= 0, scol = 0;

    Matrix arr(N, vector<int>(N,-1));

    arr[r][c] = 0;

    tromino(N, arr, srow, scol, r, c);
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << arr[i][j] << " ";
        }

        cout << endl;
        
    }

    


    return 0;    
}

