#include <iostream>
#include <vector>
using namespace std;

int cnt=0;
int threshold;
typedef vector<vector<int> > vector2d;
typedef vector<int> vector1d;

void input(vector2d& v, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> v[i][j];
        }
    }
}

void makeSubMatrix(int m, vector2d& A, vector2d& A11, vector2d& A12, vector2d& A21, vector2d& A22){
    //A11
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+m];
            A21[i][j] = A[i+m][j];
            A22[i][j] = A[i+m][j+m];
        }
    }
}

void madd(int n, vector2d& A, vector2d& B, vector2d& C){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void msub(int n, vector2d& A, vector2d& B, vector2d& C){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void mmult(int n, vector2d& A, vector2d& B, vector2d& C){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
               C[i][j] += A[i][k] * B[k][j];
}

void combine(int n, vector2d& A, vector2d& A11, vector2d& A12, vector2d& A21, vector2d& A22){

    int m = n / 2;
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            A[i][j] = A11[i][j];
            A[i][j+m] = A12[i][j];
            A[i+m][j] = A21[i][j];
            A[i+m][j+m] = A22[i][j];
        }
    }
}

void strassen(int n, vector2d& A, vector2d& B, vector2d& C){
    cnt++;
    if(n <= threshold){
        mmult(n, A, B, C);
    }
    else {
        int m = n/2;
        //1. make A, B into four subMatrixes
        vector2d A11(m, vector1d(m,0)); vector2d A12(m, vector1d(m,0)); vector2d A21(m, vector1d(m,0)); vector2d A22(m, vector1d(m,0));
        vector2d B11(m, vector1d(m,0)); vector2d B12(m, vector1d(m,0)); vector2d B21(m, vector1d(m,0)); vector2d B22(m, vector1d(m,0));
        vector2d C11(m, vector1d(m,0)); vector2d C12(m, vector1d(m,0)); vector2d C21(m, vector1d(m,0)); vector2d C22(m, vector1d(m,0));
        makeSubMatrix(m, A, A11, A12, A21, A22);
        makeSubMatrix(m, B, B11, B12, B21, B22);

        vector2d M1(m, vector1d(m,0)); vector2d M2(m, vector1d(m,0)); vector2d M3(m, vector1d(m,0)); vector2d M4(m, vector1d(m,0));
        vector2d M5(m, vector1d(m,0)); vector2d M6(m, vector1d(m,0)); vector2d M7(m, vector1d(m,0)); 
        vector2d t1(m, vector1d(m,0)); vector2d t2(m, vector1d(m,0)); 

        //M1
        madd(m, A11, A22, t1);
        madd(m, B11, B22, t2);
        strassen(m, t1, t2, M1);

        //M2
        madd(m, A21, A22, t1);
        strassen(m, t1, B11, M2);

        //M3
        msub(m, B12, B22, t1);
        strassen(m, A11, t1, M3);

        //M4
        msub(m, B21, B11, t1);
        strassen(m, A22, t1, M4);

        //M5
        madd(m, A11, A12, t1);
        strassen(m, t1, B22, M5);

        //M6
        msub(m, A21, A11, t1);
        madd(m, B11, B12, t2);
        strassen(m, t1, t2, M6);

        //M7
        msub(m, A12, A22, t1);
        madd(m, B21, B22, t2);
        strassen(m, t1, t2, M7);

        //3. make C with M1 ~ M7 -> you might need add, sub
        //C11
        madd(m, M1, M4, t1);
        msub(m, t1, M5, t2);
        madd(m, t2, M7, C11);

        //C12
        madd(m, M3, M5, C12);

        //C21
        madd(m, M2, M4, C21);

        //C22
        madd(m, M1, M3, t1);
        msub(m, t1, M2, t2);
        madd(m, t2, M6, C22);

        //4. combine C11 ~ C22 into the only C 
        combine(n, C, C11, C12, C21, C22);
    }
}

void print(int n, vector2d& v){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << v[i][j];
            if(j == n-1) cout << "\n";
            else cout << " ";
        }
    }
}

int makeIt2x(int n){
    int ans = 2;
    while(1){
        if(n <= ans) break;
        ans *= 2;
    }
    return ans;
}


int main(){

    int n, ntemp;
    cin >> ntemp >> threshold;
    n = makeIt2x(ntemp);

    vector2d v1(n, vector1d(n,0));
    vector2d v2(n, vector1d(n,0));
    vector2d v3(n, vector1d(n,0));

    input(v1, ntemp);
    input(v2, ntemp);

    strassen(n, v1, v2, v3);

    cout << cnt << "\n";
    print(ntemp, v3);

    return 0;
}