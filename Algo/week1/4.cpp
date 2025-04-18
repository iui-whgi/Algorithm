#include <iostream>
#include <vector>
using namespace std;

// <> 안에 타입을 지정해주는걸 보고,
// c++ container, template
// java generic
typedef vector<vector<int> > matrix_t;

void matrixmult(int n, matrix_t& A, matrix_t& B, matrix_t& C){

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int sum =0;
            for(int k=1; k<=n; k++){
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

}

int main(){

    int n;
    cin >> n;

    // vector<int< S(n,0) -> n개의 공간을 만들고, 0으로 초기화
    matrix_t A(n+1, vector<int>(n+1));
    matrix_t B(n+1, vector<int>(n+1));
    matrix_t C(n+1, vector<int>(n+1));

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> A[i][j];
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> B[i][j];
        }
    }

    matrixmult(n, A, B, C);

    for(int i=1; i<=n; i++){
        cout << C[i][1];
        for(int j=2; j<=n; j++){
            cout  << " " << C[i][j];
        }
        cout << endl;
    }

    return 0;
}

