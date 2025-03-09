
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

typedef vector<vector<int>> matrix_t;
void matrixmult(int n, matrix_t A, matrix_t B, matrix_t& C)
{
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            C[i][j] = 0;
            for(int k = 1; k<=n ; k++){ // ! 여기서 =을 안넣음
                C[i][j] += A[i][k]* B[k][j];
            }
        }
    }

}


int main() {

    int N;
    cin >> N;

    vector<matrix_t> matrices(N, matrix_t(N+1, vector<int>(N+1)));
    for (int k = 0; k < N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> matrices[k][i][j];
            }
        }
    }

    matrix_t result(N+1, vector<int>(N+1));
    matrix_t temp = matrices[0];
    

    for (int k = 1; k < N; k++) {
        matrixmult(N, temp, matrices[k], result);
        temp = result;
    }

    // cout << matrices[0][1][2] << endl;
    // cout << matrices[0][2][1] << endl;
    // cout << matrices[1][2][1] << endl;
    // cout << "Result:" << endl;

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //         cout << result[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 1; i <= N; i++) {
        cout << result[i][1];
        for (int j = 2; j <= N; j++) {
            cout << " " << result[i][j];
        }
        cout << endl;
    }


}